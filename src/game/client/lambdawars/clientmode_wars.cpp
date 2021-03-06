//====== Copyright � Sandern Corporation, All rights reserved. ===========//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "clientmode_wars.h"
#include "vgui_int.h"
#include "ienginevgui.h"
#include "cdll_client_int.h"
#include "engine/IEngineSound.h"

#include "vgui/hl2warsviewport.h"
#include "wars_loading_panel.h"
#include "wars_logo_panel.h"
#include "ivmodemanager.h"
#include "panelmetaclassmgr.h"
#include "nb_header_footer.h"
#include "glow_outline_effect.h"
#include "c_hl2wars_player.h"
#include "viewpostprocess.h"

#ifdef ENABLE_CEF
#include "src_cef.h"
#endif // ENABLE_CEF

#ifdef ENABLE_PYTHON
	#include "srcpy.h"
#endif // ENABLE_PYTHON

#include "vgui/surface_passthru.h"
#include <vgui_controls/Controls.h>
#include <vgui/IInput.h>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

ConVar default_fov( "default_fov", "75", FCVAR_CHEAT );
ConVar fov_desired( "fov_desired", "75", FCVAR_USERINFO, "Sets the base field-of-view.", true, 1.0, true, 75.0 );

vgui::HScheme g_hVGuiCombineScheme = 0;

vgui::DHANDLE<CSDK_Logo_Panel> g_hLogoPanel;

static IClientMode *g_pClientMode[ MAX_SPLITSCREEN_PLAYERS ];
IClientMode *GetClientMode()
{
	ASSERT_LOCAL_PLAYER_RESOLVABLE();
	return g_pClientMode[ GET_ACTIVE_SPLITSCREEN_SLOT() ];
}

// --------------------------------------------------------------------------------- //
// Mouse cursor overriding.
// --------------------------------------------------------------------------------- //
extern vgui::ISurface *g_pVGuiSurface;

class SurfaceCursorOverride : public CSurfacePassThru
{
public:
	SurfaceCursorOverride();

	virtual void InitPassThru( ISurface *pSurfacePassThru );

	void SetCursor(HCursor cursor);

private:
	vgui::HCursor m_hArrow;
};

SurfaceCursorOverride::SurfaceCursorOverride()
{
}

void SurfaceCursorOverride::InitPassThru( ISurface *pSurfacePassThru )
{
	CSurfacePassThru::InitPassThru( pSurfacePassThru );

	m_hArrow = vgui::surface()->CreateCursorFromFile( "resource/arrows/default_cursor.cur" );
}

void SurfaceCursorOverride::SetCursor(HCursor cursor)
{
	if( cursor == dc_arrow )
	{
		cursor = m_hArrow;
	}

	CSurfacePassThru::SetCursor( cursor );
}

static SurfaceCursorOverride s_SurfacePassThru;

// Voice data
void VoxCallback( IConVar *var, const char *oldString, float oldFloat )
{
	if ( engine && engine->IsConnected() )
	{
		ConVarRef voice_vox( var->GetName() );
		if ( voice_vox.GetBool() /*&& voice_modenable.GetBool()*/ )
		{
			engine->ClientCmd( "voicerecord_toggle on\n" );
		}
		else
		{
			engine->ClientCmd( "voicerecord_toggle off\n" );
		}
	}
}
ConVar voice_vox( "voice_vox", "0", FCVAR_ARCHIVE, "Voice chat uses a vox-style always on", false, 0, true, 1, VoxCallback );

//--------------------------------------------------------------------------------------------------------
class CVoxManager : public CAutoGameSystem
{
public:
	CVoxManager() : CAutoGameSystem( "VoxManager" ) { }

	virtual void LevelInitPostEntity( void )
	{
		if ( voice_vox.GetBool() /*&& voice_modenable.GetBool()*/ )
		{
			engine->ClientCmd( "voicerecord_toggle on\n" );
		}
	}


	virtual void LevelShutdownPreEntity( void )
	{
		if ( voice_vox.GetBool() )
		{
			engine->ClientCmd( "voicerecord_toggle off\n" );
		}
	}
};


//--------------------------------------------------------------------------------------------------------
static CVoxManager s_VoxManager;

// --------------------------------------------------------------------------------- //
// CSDKModeManager.
// --------------------------------------------------------------------------------- //

class CSDKModeManager : public IVModeManager
{
public:
	virtual void	Init();
	virtual void	SwitchMode( bool commander, bool force ) {}
	virtual void	LevelInit( const char *newmap );
	virtual void	LevelShutdown( void );
	virtual void	ActivateMouse( bool isactive ) {}
};

static CSDKModeManager g_ModeManager;
IVModeManager *modemanager = ( IVModeManager * )&g_ModeManager;



// --------------------------------------------------------------------------------- //
// CASWModeManager implementation.
// --------------------------------------------------------------------------------- //

#define SCREEN_FILE		"scripts/vgui_screens.txt"

void CSDKModeManager::Init()
{
	for( int i = 0; i < MAX_SPLITSCREEN_PLAYERS; ++i )
	{
		ACTIVE_SPLITSCREEN_PLAYER_GUARD( i );
		g_pClientMode[ i ] = GetClientModeNormal();
	}

	PanelMetaClassMgr()->LoadMetaClassDefinitionFile( SCREEN_FILE );

	//GetClientVoiceMgr()->SetHeadLabelOffset( 40 );
}

void CSDKModeManager::LevelInit( const char *newmap )
{
	for( int i = 0; i < MAX_SPLITSCREEN_PLAYERS; ++i )
	{
		ACTIVE_SPLITSCREEN_PLAYER_GUARD( i );
		GetClientMode()->LevelInit( newmap );
	}
}

void CSDKModeManager::LevelShutdown( void )
{
	for( int i = 0; i < MAX_SPLITSCREEN_PLAYERS; ++i )
	{
		ACTIVE_SPLITSCREEN_PLAYER_GUARD( i );
		GetClientMode()->LevelShutdown();
	}
}

ClientModeSDK g_ClientModeNormal[ MAX_SPLITSCREEN_PLAYERS ];
IClientMode *GetClientModeNormal()
{
	ASSERT_LOCAL_PLAYER_RESOLVABLE();
	return &g_ClientModeNormal[ GET_ACTIVE_SPLITSCREEN_SLOT() ];
}

ClientModeSDK* GetClientModeSDK()
{
	ASSERT_LOCAL_PLAYER_RESOLVABLE();
	return &g_ClientModeNormal[ GET_ACTIVE_SPLITSCREEN_SLOT() ];
}

// these vgui panels will be closed at various times (e.g. when the level ends/starts)
static char const *s_CloseWindowNames[]={
	"InfoMessageWindow",
	"SkipIntro",
};

//--------------------------------------------------------------------------------------------------------

// See interface.h/.cpp for specifics:  basically this ensures that we actually Sys_UnloadModule the dll and that we don't call Sys_LoadModule 
//  over and over again.
static CDllDemandLoader g_GameUI( "gameui" );

class FullscreenSDKViewport : public HL2WarsViewport
{
private:
	DECLARE_CLASS_SIMPLE( FullscreenSDKViewport, HL2WarsViewport );

private:
	virtual void InitViewportSingletons( void )
	{
		SetAsFullscreenViewportInterface();
	}
};

class ClientModeSDKFullscreen : public	ClientModeSDK
{
	DECLARE_CLASS_SIMPLE( ClientModeSDKFullscreen, ClientModeSDK );
public:
	virtual void InitViewport()
	{
		// Skip over BaseClass!!!
		BaseClass::BaseClass::InitViewport();
		m_pViewport = new FullscreenSDKViewport();
		m_pViewport->Start( gameuifuncs, gameeventmanager );
	}
	virtual void Init()
	{
		CreateInterfaceFn gameUIFactory = g_GameUI.GetFactory();
		if ( gameUIFactory )
		{
			IGameUI *pGameUI = (IGameUI *) gameUIFactory(GAMEUI_INTERFACE_VERSION, NULL );
			if ( NULL != pGameUI )
			{
				// insert stats summary panel as the loading background dialog
				CSDK_Loading_Panel *pPanel = GSDKLoadingPanel();
				pPanel->InvalidateLayout( false, true );
				pPanel->SetVisible( false );
				pPanel->MakePopup( false );
				pGameUI->SetLoadingBackgroundDialog( pPanel->GetVPanel() );
			}		
		}

		// 
		//CASW_VGUI_Debug_Panel *pDebugPanel = new CASW_VGUI_Debug_Panel( GetViewport(), "ASW Debug Panel" );
		//g_hDebugPanel = pDebugPanel;

		// Skip over BaseClass!!!
		BaseClass::BaseClass::Init();

		// Load up the combine control panel scheme
		if ( !g_hVGuiCombineScheme )
		{
			g_hVGuiCombineScheme = vgui::scheme()->LoadSchemeFromFileEx( enginevgui->GetPanel( PANEL_CLIENTDLL ), IsXbox() ? "resource/ClientScheme.res" : "resource/CombinePanelScheme.res", "CombineScheme" );
			if (!g_hVGuiCombineScheme)
			{
				Warning( "Couldn't load combine panel scheme!\n" );
			}
		}
	}
	void Shutdown()
	{
		DestroySDKLoadingPanel();
		if (g_hLogoPanel.Get())
		{
			delete g_hLogoPanel.Get();
		}
	}
};

//--------------------------------------------------------------------------------------------------------
IClientMode *GetFullscreenClientMode( void )
{
	static ClientModeSDKFullscreen g_FullscreenClientMode;
	return &g_FullscreenClientMode;
}

ClientModeSDK::ClientModeSDK()
{
	m_pCurrentPostProcessController = NULL;
	m_PostProcessLerpTimer.Invalidate();
	m_pCurrentColorCorrection = NULL;
}

void ClientModeSDK::Init()
{
	BaseClass::Init();

	// Overrides dc_arrow (and possible other cursors)
	s_SurfacePassThru.InitPassThru( g_pVGuiSurface );
	g_pVGuiSurface = &s_SurfacePassThru;

	gameeventmanager->AddListener( this, "game_newmap", false );
}
void ClientModeSDK::Shutdown()
{
	// Clear cursor overrider
	g_pVGuiSurface = s_SurfacePassThru.GetRealSurface();

	if ( SDKBackgroundMovie() )
	{
		SDKBackgroundMovie()->ClearCurrentMovie();
	}
	DestroySDKLoadingPanel();
	if (g_hLogoPanel.Get())
	{
		delete g_hLogoPanel.Get();
	}
}

void ClientModeSDK::InitViewport()
{
	m_pViewport = new HL2WarsViewport();
	m_pViewport->Start( gameuifuncs, gameeventmanager );
}

void ClientModeSDK::LevelInit( const char *newmap )
{
	// reset ambient light
	static ConVarRef mat_ambient_light_r( "mat_ambient_light_r" );
	static ConVarRef mat_ambient_light_g( "mat_ambient_light_g" );
	static ConVarRef mat_ambient_light_b( "mat_ambient_light_b" );

	if ( mat_ambient_light_r.IsValid() )
	{
		mat_ambient_light_r.SetValue( "0" );
	}

	if ( mat_ambient_light_g.IsValid() )
	{
		mat_ambient_light_g.SetValue( "0" );
	}

	if ( mat_ambient_light_b.IsValid() )
	{
		mat_ambient_light_b.SetValue( "0" );
	}

	BaseClass::LevelInit(newmap);

	// sdk: make sure no windows are left open from before
	SDK_CloseAllWindows();

	// clear any DSP effects
	CLocalPlayerFilter filter;
	enginesound->SetRoomType( filter, 0 );
	enginesound->SetPlayerDSP( filter, 0, true );
}

void ClientModeSDK::LevelShutdown( void )
{
	BaseClass::LevelShutdown();

	// sdk:shutdown all vgui windows
	SDK_CloseAllWindows();
}
void ClientModeSDK::FireGameEvent( IGameEvent *event )
{
	const char *eventname = event->GetName();

	if ( Q_strcmp( "asw_mission_restart", eventname ) == 0 )
	{
		SDK_CloseAllWindows();
	}
	else if ( Q_strcmp( "game_newmap", eventname ) == 0 )
	{
		engine->ClientCmd("exec newmapsettings\n");
	}
	else
	{
		BaseClass::FireGameEvent(event);
	}
}
// Close all ASW specific VGUI windows that the player might have open
void ClientModeSDK::SDK_CloseAllWindows()
{
	SDK_CloseAllWindowsFrom(GetViewport());
}

// recursive search for matching window names
void ClientModeSDK::SDK_CloseAllWindowsFrom(vgui::Panel* pPanel)
{
	if (!pPanel)
		return;

	int num_names = NELEMS(s_CloseWindowNames);

	for (int k=0;k<pPanel->GetChildCount();k++)
	{
		Panel *pChild = pPanel->GetChild(k);
		if (pChild)
		{
			SDK_CloseAllWindowsFrom(pChild);
		}
	}

	// When VGUI is shutting down (i.e. if the player closes the window), GetName() can return NULL
	const char *pPanelName = pPanel->GetName();
	if ( pPanelName != NULL )
	{
		for (int i=0;i<num_names;i++)
		{
			if ( !strcmp( pPanelName, s_CloseWindowNames[i] ) )
			{
				pPanel->SetVisible(false);
				pPanel->MarkForDeletion();
			}
		}
	}
}

int	ClientModeSDK::KeyInput( int down, ButtonCode_t keynum, const char *pszCurrentBinding )
{
	if ( engine->Con_IsVisible() )
		return 1;

	// Use escape to leave control
	if (keynum == KEY_ESCAPE)
	{
		C_HL2WarsPlayer *pPlayer = C_HL2WarsPlayer::GetLocalHL2WarsPlayer();
		if( pPlayer && pPlayer->GetControlledUnit() )
		{
			engine->ClientCmd( "player_release_control_unit" );
			return 0;
		}
	}

#ifdef ENABLE_CEF
	// Pass input to cef browser if they want it
	int ret = CEFSystem().KeyInput( down, keynum, pszCurrentBinding );
	if( ret == 0 )
		return 0;
#endif // ENABLE_CEF

	// Should we start typing a message?
	if ( pszCurrentBinding &&
		( Q_strcmp( pszCurrentBinding, "messagemode" ) == 0 ||
		Q_strcmp( pszCurrentBinding, "say" ) == 0 ) )
	{
		if ( down )
		{
#ifdef ENABLE_PYTHON
			bool bShift = input()->IsKeyDown( KEY_LSHIFT ) || input()->IsKeyDown( KEY_RSHIFT );

			if( SrcPySystem()->IsPythonRunning() )
			{
				try 
				{
					// Tell python
					boost::python::dict kwargs;
					kwargs["sender"] = boost::python::object();
					kwargs["mode"] = (int)(bShift ? MM_SAY_TEAM : MM_SAY);
					boost::python::object signal = SrcPySystem()->Get( "startclientchat", "core.signals", true );
					SrcPySystem()->CallSignal( signal, kwargs );
				} 
				catch( boost::python::error_already_set & ) 
				{
					Warning( "Failed to dispatch chat start signal" );
					PyErr_Print();
				}
			}
#endif // ENABLE_PYTHON
		}
		return 0;
	}
	else if ( pszCurrentBinding &&
		( Q_strcmp( pszCurrentBinding, "messagemode2" ) == 0 ||
		Q_strcmp( pszCurrentBinding, "say_team" ) == 0 ) )
	{
		if ( down )
		{
#ifdef ENABLE_PYTHON
			if( SrcPySystem()->IsPythonRunning() )
			{
				try 
				{
					// Tell python
					boost::python::dict kwargs;
					kwargs["sender"] = boost::python::object();
					kwargs["mode"] = (int)MM_SAY_TEAM;
					boost::python::object signal = SrcPySystem()->Get( "startclientchat", "core.signals", true );
					SrcPySystem()->CallSignal( signal, kwargs );
				} 
				catch( boost::python::error_already_set & ) 
				{
					Warning( "Failed to dispatch chat start signal" );
					PyErr_Print();
				}
			}
#endif // ENABLE_PYTHON
		}
		return 0;
	}

	return BaseClass::KeyInput(down, keynum, pszCurrentBinding);
}

void ClientModeSDK::DoPostScreenSpaceEffects( const CViewSetup *pSetup )
{
	CMatRenderContextPtr pRenderContext( materials );

	g_GlowObjectManager.RenderGlowEffects( pSetup, 0 /*GetSplitScreenPlayerSlot()*/ );
}

void ClientModeSDK::OnColorCorrectionWeightsReset( void )
{
	C_ColorCorrection *pNewColorCorrection = NULL;
	C_ColorCorrection *pOldColorCorrection = m_pCurrentColorCorrection;

	C_HL2WarsPlayer *pPlayer = C_HL2WarsPlayer::GetLocalHL2WarsPlayer();
	if ( pPlayer )
	{
		pNewColorCorrection = pPlayer->GetActiveColorCorrection();
	}

	// Only blend between environmental color corrections if there is no failure/infested-induced color correction
	if ( pNewColorCorrection != pOldColorCorrection /*&& m_fFailedCCWeight == 0.0f && m_fInfestedCCWeight == 0.0f*/ )
	{
		if ( pOldColorCorrection )
		{
			pOldColorCorrection->EnableOnClient( false );
		}
		if ( pNewColorCorrection )
		{
			pNewColorCorrection->EnableOnClient( true, pOldColorCorrection == NULL );
		}
		m_pCurrentColorCorrection = pNewColorCorrection;
	}
}

void ClientModeSDK::Update( void )
{
	BaseClass::Update();

	UpdatePostProcessingEffects();
}

void ClientModeSDK::UpdatePostProcessingEffects()
{
	C_PostProcessController *pNewPostProcessController = NULL;
	C_HL2WarsPlayer *pPlayer = C_HL2WarsPlayer::GetLocalHL2WarsPlayer();
	if ( pPlayer )
	{
		pNewPostProcessController = pPlayer->GetActivePostProcessController();
	}

	// Figure out new endpoints for parameter lerping
	if ( pNewPostProcessController != m_pCurrentPostProcessController )
	{
		m_LerpStartPostProcessParameters = m_CurrentPostProcessParameters;
		m_LerpEndPostProcessParameters = pNewPostProcessController ? pNewPostProcessController->m_PostProcessParameters : PostProcessParameters_t();
		m_pCurrentPostProcessController = pNewPostProcessController;

		float flFadeTime = pNewPostProcessController ? pNewPostProcessController->m_PostProcessParameters.m_flParameters[ PPPN_FADE_TIME ] : 0.0f;
		if ( flFadeTime <= 0.0f )
		{
			flFadeTime = 0.001f;
		}
		m_PostProcessLerpTimer.Start( flFadeTime );
	}

	// Lerp between start and end
	float flLerpFactor = 1.0f - m_PostProcessLerpTimer.GetRemainingRatio();
	for ( int nParameter = 0; nParameter < POST_PROCESS_PARAMETER_COUNT; ++ nParameter )
	{
		m_CurrentPostProcessParameters.m_flParameters[ nParameter ] = 
			Lerp( 
				flLerpFactor, 
				m_LerpStartPostProcessParameters.m_flParameters[ nParameter ], 
				m_LerpEndPostProcessParameters.m_flParameters[ nParameter ] );
	}
	SetPostProcessParams( &m_CurrentPostProcessParameters );
}