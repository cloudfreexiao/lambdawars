// This file has been generated by Py++.

#include "cbase.h"
#ifdef CLIENT_DLL
#include "__array_1.pypp.hpp"

#include "wchar.h"

#include "string_t.h"

#include "cbase.h"

#include "shareddefs.h"

#include "srcpy_sound.h"

#include "soundflags.h"

#include "srcpy.h"

#include "tier0/memdbgon.h"

namespace bp = boost::python;

struct CSoundParameters_wrapper : CSoundParameters, bp::wrapper< CSoundParameters > {

    CSoundParameters_wrapper(CSoundParameters const & arg )
    : CSoundParameters( arg )
      , bp::wrapper< CSoundParameters >(){
        // copy constructor
        
    }

    CSoundParameters_wrapper( )
    : CSoundParameters( )
      , bp::wrapper< CSoundParameters >(){
        // null constructor
    
    }

    static pyplusplus::containers::static_sized::array_1_t< char, 128>
    pyplusplus_soundname_wrapper( ::CSoundParameters & inst ){
        return pyplusplus::containers::static_sized::array_1_t< char, 128>( inst.soundname );
    }

};

struct EmitSound_t_wrapper : EmitSound_t, bp::wrapper< EmitSound_t > {

    EmitSound_t_wrapper( )
    : EmitSound_t( )
      , bp::wrapper< EmitSound_t >(){
        // null constructor
    
    }

    EmitSound_t_wrapper(::CSoundParameters const & src )
    : EmitSound_t( src )
      , bp::wrapper< EmitSound_t >(){
        // constructor
    
    }

    static ::Vector const * get_m_pOrigin(EmitSound_t const & inst ){
        return inst.m_pOrigin;
    }
    
    static void set_m_pOrigin( EmitSound_t & inst, ::Vector const * new_value ){ 
        inst.m_pOrigin = new_value;
    }

};

BOOST_PYTHON_MODULE(_sound){
    bp::docstring_options doc_options( true, true, false );

    bp::enum_< soundcommands_t>("soundcommands")
        .value("SOUNDCTRL_CHANGE_VOLUME", SOUNDCTRL_CHANGE_VOLUME)
        .value("SOUNDCTRL_CHANGE_PITCH", SOUNDCTRL_CHANGE_PITCH)
        .value("SOUNDCTRL_STOP", SOUNDCTRL_STOP)
        .value("SOUNDCTRL_DESTROY", SOUNDCTRL_DESTROY)
        .export_values()
        ;

    bp::enum_< soundlevel_t>("soundlevel")
        .value("SNDLVL_NONE", SNDLVL_NONE)
        .value("SNDLVL_20dB", SNDLVL_20dB)
        .value("SNDLVL_25dB", SNDLVL_25dB)
        .value("SNDLVL_30dB", SNDLVL_30dB)
        .value("SNDLVL_35dB", SNDLVL_35dB)
        .value("SNDLVL_40dB", SNDLVL_40dB)
        .value("SNDLVL_45dB", SNDLVL_45dB)
        .value("SNDLVL_50dB", SNDLVL_50dB)
        .value("SNDLVL_55dB", SNDLVL_55dB)
        .value("SNDLVL_IDLE", SNDLVL_IDLE)
        .value("SNDLVL_60dB", SNDLVL_60dB)
        .value("SNDLVL_65dB", SNDLVL_65dB)
        .value("SNDLVL_STATIC", SNDLVL_STATIC)
        .value("SNDLVL_70dB", SNDLVL_70dB)
        .value("SNDLVL_NORM", SNDLVL_NORM)
        .value("SNDLVL_75dB", SNDLVL_75dB)
        .value("SNDLVL_80dB", SNDLVL_80dB)
        .value("SNDLVL_TALKING", SNDLVL_TALKING)
        .value("SNDLVL_85dB", SNDLVL_85dB)
        .value("SNDLVL_90dB", SNDLVL_90dB)
        .value("SNDLVL_95dB", SNDLVL_95dB)
        .value("SNDLVL_100dB", SNDLVL_100dB)
        .value("SNDLVL_105dB", SNDLVL_105dB)
        .value("SNDLVL_110dB", SNDLVL_110dB)
        .value("SNDLVL_120dB", SNDLVL_120dB)
        .value("SNDLVL_130dB", SNDLVL_130dB)
        .value("SNDLVL_GUNFIRE", SNDLVL_GUNFIRE)
        .value("SNDLVL_140dB", SNDLVL_140dB)
        .value("SNDLVL_150dB", SNDLVL_150dB)
        .value("SNDLVL_180dB", SNDLVL_180dB)
        .export_values()
        ;

    bp::class_< CSoundEnvelopeControllerHandle >( "CSoundEnvelopeController", bp::no_init )    
        .def( 
            "CheckLoopingSoundsForPlayer"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::C_BasePlayer * ) )( &::CSoundEnvelopeControllerHandle::CheckLoopingSoundsForPlayer )
            , ( bp::arg("pPlayer") ) )    
        .def( 
            "CommandAdd"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float,::soundcommands_t,float,float ) )( &::CSoundEnvelopeControllerHandle::CommandAdd )
            , ( bp::arg("pSound"), bp::arg("executeDeltaTime"), bp::arg("command"), bp::arg("commandTime"), bp::arg("value") ) )    
        .def( 
            "CommandClear"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::CommandClear )
            , ( bp::arg("pSound") ) )    
        .def( 
            "GetController"
            , (::CSoundEnvelopeControllerHandle (*)(  ))( &::CSoundEnvelopeControllerHandle::GetController ) )    
        .def( 
            "Play"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float,float,float ) )( &::CSoundEnvelopeControllerHandle::Play )
            , ( bp::arg("pSound"), bp::arg("volume"), bp::arg("pitch"), bp::arg("flStartTime")=0 ) )    
        .def( 
            "Shutdown"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::Shutdown )
            , ( bp::arg("pSound") ) )    
        .def( 
            "SoundChangePitch"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float,float ) )( &::CSoundEnvelopeControllerHandle::SoundChangePitch )
            , ( bp::arg("pSound"), bp::arg("pitchTarget"), bp::arg("deltaTime") ) )    
        .def( 
            "SoundChangeVolume"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float,float ) )( &::CSoundEnvelopeControllerHandle::SoundChangeVolume )
            , ( bp::arg("pSound"), bp::arg("volumeTarget"), bp::arg("deltaTime") ) )    
        .def( 
            "SoundCreate"
            , (::CSoundPatchHandle ( ::CSoundEnvelopeControllerHandle::* )( ::IRecipientFilter &,int,char const * ) )( &::CSoundEnvelopeControllerHandle::SoundCreate )
            , ( bp::arg("filter"), bp::arg("nEntIndex"), bp::arg("pSoundName") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "SoundCreate"
            , (::CSoundPatchHandle ( ::CSoundEnvelopeControllerHandle::* )( ::IRecipientFilter &,int,int,char const *,float ) )( &::CSoundEnvelopeControllerHandle::SoundCreate )
            , ( bp::arg("filter"), bp::arg("nEntIndex"), bp::arg("channel"), bp::arg("pSoundName"), bp::arg("attenuation") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "SoundCreate"
            , (::CSoundPatchHandle ( ::CSoundEnvelopeControllerHandle::* )( ::IRecipientFilter &,int,int,char const *,::soundlevel_t ) )( &::CSoundEnvelopeControllerHandle::SoundCreate )
            , ( bp::arg("filter"), bp::arg("nEntIndex"), bp::arg("channel"), bp::arg("pSoundName"), bp::arg("soundlevel") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "SoundCreate"
            , (::CSoundPatchHandle ( ::CSoundEnvelopeControllerHandle::* )( ::IRecipientFilter &,int,::EmitSound_t const & ) )( &::CSoundEnvelopeControllerHandle::SoundCreate )
            , ( bp::arg("filter"), bp::arg("nEntIndex"), bp::arg("es") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "SoundDestroy"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::SoundDestroy )
            , ( bp::arg("pSound") ) )    
        .def( 
            "SoundFadeOut"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float,bool ) )( &::CSoundEnvelopeControllerHandle::SoundFadeOut )
            , ( bp::arg("pSound"), bp::arg("deltaTime"), bp::arg("destroyOnFadeout")=(bool)(false) ) )    
        .def( 
            "SoundGetName"
            , (::string_t ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::SoundGetName )
            , ( bp::arg("pSound") ) )    
        .def( 
            "SoundGetPitch"
            , (float ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::SoundGetPitch )
            , ( bp::arg("pSound") ) )    
        .def( 
            "SoundGetVolume"
            , (float ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::SoundGetVolume )
            , ( bp::arg("pSound") ) )    
        .def( 
            "SoundSetCloseCaptionDuration"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float ) )( &::CSoundEnvelopeControllerHandle::SoundSetCloseCaptionDuration )
            , ( bp::arg("pSound"), bp::arg("flDuration") ) )    
        .def( 
            "SystemReset"
            , (void ( ::CSoundEnvelopeControllerHandle::* )(  ) )( &::CSoundEnvelopeControllerHandle::SystemReset ) )    
        .def( 
            "SystemUpdate"
            , (void ( ::CSoundEnvelopeControllerHandle::* )(  ) )( &::CSoundEnvelopeControllerHandle::SystemUpdate ) )    
        .staticmethod( "GetController" );

    { //::CSoundParameters
        typedef bp::class_< CSoundParameters_wrapper > CSoundParameters_exposer_t;
        CSoundParameters_exposer_t CSoundParameters_exposer = CSoundParameters_exposer_t( "CSoundParameters", bp::init< >() );
        bp::scope CSoundParameters_scope( CSoundParameters_exposer );
        CSoundParameters_exposer.def_readwrite( "channel", &CSoundParameters::channel );
        CSoundParameters_exposer.def_readwrite( "count", &CSoundParameters::count );
        CSoundParameters_exposer.def_readwrite( "delay_msec", &CSoundParameters::delay_msec );
        CSoundParameters_exposer.def_readwrite( "pitch", &CSoundParameters::pitch );
        CSoundParameters_exposer.def_readwrite( "pitchhigh", &CSoundParameters::pitchhigh );
        CSoundParameters_exposer.def_readwrite( "pitchlow", &CSoundParameters::pitchlow );
        CSoundParameters_exposer.def_readwrite( "play_to_owner_only", &CSoundParameters::play_to_owner_only );
        CSoundParameters_exposer.def_readwrite( "soundlevel", &CSoundParameters::soundlevel );
        pyplusplus::containers::static_sized::register_array_1< char, 128 >( "__array_1_char_128" );
        { //CSoundParameters::soundname [variable], type=char[128]
        
            typedef pyplusplus::containers::static_sized::array_1_t< char, 128> ( *array_wrapper_creator )( ::CSoundParameters & );
            
            CSoundParameters_exposer.add_property( "soundname"
                , bp::make_function( array_wrapper_creator(&CSoundParameters_wrapper::pyplusplus_soundname_wrapper)
                                    , bp::with_custodian_and_ward_postcall< 0, 1 >() ) );
        }
        CSoundParameters_exposer.def_readwrite( "volume", &CSoundParameters::volume );
    }

    bp::class_< CSoundPatchHandle >( "CSoundPatch", bp::no_init );

    { //::EmitSound_t
        typedef bp::class_< EmitSound_t_wrapper, boost::noncopyable > EmitSound_exposer_t;
        EmitSound_exposer_t EmitSound_exposer = EmitSound_exposer_t( "EmitSound", bp::init< >() );
        bp::scope EmitSound_scope( EmitSound_exposer );
        EmitSound_exposer.def( bp::init< CSoundParameters const & >(( bp::arg("src") )) );
        bp::implicitly_convertible< CSoundParameters const &, EmitSound_t >();
        EmitSound_exposer.def_readwrite( "soundlevel", &EmitSound_t::m_SoundLevel );
        EmitSound_exposer.def_readwrite( "emitclosecaption", &EmitSound_t::m_bEmitCloseCaption );
        EmitSound_exposer.def_readwrite( "warnondirectwavereference", &EmitSound_t::m_bWarnOnDirectWaveReference );
        EmitSound_exposer.def_readwrite( "warnonmissingclosecaption", &EmitSound_t::m_bWarnOnMissingCloseCaption );
        EmitSound_exposer.def_readwrite( "soundtime", &EmitSound_t::m_flSoundTime );
        EmitSound_exposer.def_readwrite( "volume", &EmitSound_t::m_flVolume );
        EmitSound_exposer.def_readwrite( "soundscripthandle", &EmitSound_t::m_hSoundScriptHandle );
        EmitSound_exposer.def_readwrite( "channel", &EmitSound_t::m_nChannel );
        EmitSound_exposer.def_readwrite( "flags", &EmitSound_t::m_nFlags );
        EmitSound_exposer.def_readwrite( "pitch", &EmitSound_t::m_nPitch );
        EmitSound_exposer.def_readwrite( "speakerentity", &EmitSound_t::m_nSpeakerEntity );
        EmitSound_exposer.add_property( "origin"
                    , bp::make_function( (::Vector const * (*)( ::EmitSound_t const & ))(&EmitSound_t_wrapper::get_m_pOrigin), bp::return_internal_reference< >() )
                    , bp::make_function( (void (*)( ::EmitSound_t &,::Vector const * ))(&EmitSound_t_wrapper::set_m_pOrigin), bp::with_custodian_and_ward_postcall< 1, 2 >() ) );
    }

    bp::scope().attr( "PITCH_NORM" ) = PITCH_NORM;

    bp::scope().attr( "PITCH_LOW" ) = PITCH_LOW;

    bp::scope().attr( "PITCH_HIGH" ) = PITCH_HIGH;

    { //::PyEngineSound
        typedef bp::class_< PyEngineSound > EngineSound_exposer_t;
        EngineSound_exposer_t EngineSound_exposer = EngineSound_exposer_t( "EngineSound" );
        bp::scope EngineSound_scope( EngineSound_exposer );
        { //::PyEngineSound::EmitAmbientSound
        
            typedef void ( ::PyEngineSound::*EmitAmbientSound_function_type )( char const *,float,int,int,float ) ;
            
            EngineSound_exposer.def( 
                "EmitAmbientSound"
                , EmitAmbientSound_function_type( &::PyEngineSound::EmitAmbientSound )
                , ( bp::arg("pSample"), bp::arg("flVolume"), bp::arg("iPitch")=(int)(100), bp::arg("flags")=(int)(0), bp::arg("soundtime")=0.0f ) );
        
        }
        { //::PyEngineSound::GetDistGainFromSoundLevel
        
            typedef float ( ::PyEngineSound::*GetDistGainFromSoundLevel_function_type )( ::soundlevel_t,float ) ;
            
            EngineSound_exposer.def( 
                "GetDistGainFromSoundLevel"
                , GetDistGainFromSoundLevel_function_type( &::PyEngineSound::GetDistGainFromSoundLevel )
                , ( bp::arg("soundlevel"), bp::arg("dist") ) );
        
        }
        { //::PyEngineSound::GetGuidForLastSoundEmitted
        
            typedef int ( ::PyEngineSound::*GetGuidForLastSoundEmitted_function_type )(  ) ;
            
            EngineSound_exposer.def( 
                "GetGuidForLastSoundEmitted"
                , GetGuidForLastSoundEmitted_function_type( &::PyEngineSound::GetGuidForLastSoundEmitted ) );
        
        }
        { //::PyEngineSound::GetSoundDuration
        
            typedef float ( ::PyEngineSound::*GetSoundDuration_function_type )( char const * ) ;
            
            EngineSound_exposer.def( 
                "GetSoundDuration"
                , GetSoundDuration_function_type( &::PyEngineSound::GetSoundDuration )
                , ( bp::arg("pSample") ) );
        
        }
        { //::PyEngineSound::IsSoundPrecached
        
            typedef bool ( ::PyEngineSound::*IsSoundPrecached_function_type )( char const * ) ;
            
            EngineSound_exposer.def( 
                "IsSoundPrecached"
                , IsSoundPrecached_function_type( &::PyEngineSound::IsSoundPrecached )
                , ( bp::arg("pSample") ) );
        
        }
        { //::PyEngineSound::IsSoundStillPlaying
        
            typedef bool ( ::PyEngineSound::*IsSoundStillPlaying_function_type )( int ) ;
            
            EngineSound_exposer.def( 
                "IsSoundStillPlaying"
                , IsSoundStillPlaying_function_type( &::PyEngineSound::IsSoundStillPlaying )
                , ( bp::arg("guid") ) );
        
        }
        { //::PyEngineSound::NotifyBeginMoviePlayback
        
            typedef void ( ::PyEngineSound::*NotifyBeginMoviePlayback_function_type )(  ) ;
            
            EngineSound_exposer.def( 
                "NotifyBeginMoviePlayback"
                , NotifyBeginMoviePlayback_function_type( &::PyEngineSound::NotifyBeginMoviePlayback ) );
        
        }
        { //::PyEngineSound::NotifyEndMoviePlayback
        
            typedef void ( ::PyEngineSound::*NotifyEndMoviePlayback_function_type )(  ) ;
            
            EngineSound_exposer.def( 
                "NotifyEndMoviePlayback"
                , NotifyEndMoviePlayback_function_type( &::PyEngineSound::NotifyEndMoviePlayback ) );
        
        }
        { //::PyEngineSound::PrecacheSentenceGroup
        
            typedef void ( ::PyEngineSound::*PrecacheSentenceGroup_function_type )( char const * ) ;
            
            EngineSound_exposer.def( 
                "PrecacheSentenceGroup"
                , PrecacheSentenceGroup_function_type( &::PyEngineSound::PrecacheSentenceGroup )
                , ( bp::arg("pGroupName") ) );
        
        }
        { //::PyEngineSound::PrecacheSound
        
            typedef bool ( ::PyEngineSound::*PrecacheSound_function_type )( char const *,bool,bool ) ;
            
            EngineSound_exposer.def( 
                "PrecacheSound"
                , PrecacheSound_function_type( &::PyEngineSound::PrecacheSound )
                , ( bp::arg("pSample"), bp::arg("bPreload")=(bool)(false), bp::arg("bIsUISound")=(bool)(false) ) );
        
        }
        { //::PyEngineSound::PrefetchSound
        
            typedef void ( ::PyEngineSound::*PrefetchSound_function_type )( char const * ) ;
            
            EngineSound_exposer.def( 
                "PrefetchSound"
                , PrefetchSound_function_type( &::PyEngineSound::PrefetchSound )
                , ( bp::arg("pSample") ) );
        
        }
        { //::PyEngineSound::SetPlayerDSP
        
            typedef void ( ::PyEngineSound::*SetPlayerDSP_function_type )( ::IRecipientFilter &,int,bool ) ;
            
            EngineSound_exposer.def( 
                "SetPlayerDSP"
                , SetPlayerDSP_function_type( &::PyEngineSound::SetPlayerDSP )
                , ( bp::arg("filter"), bp::arg("dspType"), bp::arg("fastReset") ) );
        
        }
        { //::PyEngineSound::SetRoomType
        
            typedef void ( ::PyEngineSound::*SetRoomType_function_type )( ::IRecipientFilter &,int ) ;
            
            EngineSound_exposer.def( 
                "SetRoomType"
                , SetRoomType_function_type( &::PyEngineSound::SetRoomType )
                , ( bp::arg("filter"), bp::arg("roomType") ) );
        
        }
        { //::PyEngineSound::SetVolumeByGuid
        
            typedef void ( ::PyEngineSound::*SetVolumeByGuid_function_type )( int,float ) ;
            
            EngineSound_exposer.def( 
                "SetVolumeByGuid"
                , SetVolumeByGuid_function_type( &::PyEngineSound::SetVolumeByGuid )
                , ( bp::arg("guid"), bp::arg("fvol") ) );
        
        }
        { //::PyEngineSound::StopAllSounds
        
            typedef void ( ::PyEngineSound::*StopAllSounds_function_type )( bool ) ;
            
            EngineSound_exposer.def( 
                "StopAllSounds"
                , StopAllSounds_function_type( &::PyEngineSound::StopAllSounds )
                , ( bp::arg("bClearBuffers") ) );
        
        }
        { //::PyEngineSound::StopSound
        
            typedef void ( ::PyEngineSound::*StopSound_function_type )( int,int,char const * ) ;
            
            EngineSound_exposer.def( 
                "StopSound"
                , StopSound_function_type( &::PyEngineSound::StopSound )
                , ( bp::arg("iEntIndex"), bp::arg("iChannel"), bp::arg("pSample") ) );
        
        }
        { //::PyEngineSound::StopSoundByGuid
        
            typedef void ( ::PyEngineSound::*StopSoundByGuid_function_type )( int ) ;
            
            EngineSound_exposer.def( 
                "StopSoundByGuid"
                , StopSoundByGuid_function_type( &::PyEngineSound::StopSoundByGuid )
                , ( bp::arg("guid") ) );
        
        }
        }bp::scope().attr( "soundengine" ) = boost::ref(pysoundengine);{
    }
}
#else
#include "__array_1.pypp.hpp"

#include "wchar.h"

#include "string_t.h"

#include "cbase.h"

#include "shareddefs.h"

#include "srcpy_sound.h"

#include "soundflags.h"

#include "srcpy.h"

#include "tier0/memdbgon.h"

namespace bp = boost::python;

struct CSoundParameters_wrapper : CSoundParameters, bp::wrapper< CSoundParameters > {

    CSoundParameters_wrapper(CSoundParameters const & arg )
    : CSoundParameters( arg )
      , bp::wrapper< CSoundParameters >(){
        // copy constructor
        
    }

    CSoundParameters_wrapper( )
    : CSoundParameters( )
      , bp::wrapper< CSoundParameters >(){
        // null constructor
    
    }

    static pyplusplus::containers::static_sized::array_1_t< char, 128>
    pyplusplus_soundname_wrapper( ::CSoundParameters & inst ){
        return pyplusplus::containers::static_sized::array_1_t< char, 128>( inst.soundname );
    }

};

struct EmitSound_t_wrapper : EmitSound_t, bp::wrapper< EmitSound_t > {

    EmitSound_t_wrapper( )
    : EmitSound_t( )
      , bp::wrapper< EmitSound_t >(){
        // null constructor
    
    }

    EmitSound_t_wrapper(::CSoundParameters const & src )
    : EmitSound_t( src )
      , bp::wrapper< EmitSound_t >(){
        // constructor
    
    }

    static ::Vector const * get_m_pOrigin(EmitSound_t const & inst ){
        return inst.m_pOrigin;
    }
    
    static void set_m_pOrigin( EmitSound_t & inst, ::Vector const * new_value ){ 
        inst.m_pOrigin = new_value;
    }

};

BOOST_PYTHON_MODULE(_sound){
    bp::docstring_options doc_options( true, true, false );

    bp::enum_< soundcommands_t>("soundcommands")
        .value("SOUNDCTRL_CHANGE_VOLUME", SOUNDCTRL_CHANGE_VOLUME)
        .value("SOUNDCTRL_CHANGE_PITCH", SOUNDCTRL_CHANGE_PITCH)
        .value("SOUNDCTRL_STOP", SOUNDCTRL_STOP)
        .value("SOUNDCTRL_DESTROY", SOUNDCTRL_DESTROY)
        .export_values()
        ;

    bp::enum_< soundlevel_t>("soundlevel")
        .value("SNDLVL_NONE", SNDLVL_NONE)
        .value("SNDLVL_20dB", SNDLVL_20dB)
        .value("SNDLVL_25dB", SNDLVL_25dB)
        .value("SNDLVL_30dB", SNDLVL_30dB)
        .value("SNDLVL_35dB", SNDLVL_35dB)
        .value("SNDLVL_40dB", SNDLVL_40dB)
        .value("SNDLVL_45dB", SNDLVL_45dB)
        .value("SNDLVL_50dB", SNDLVL_50dB)
        .value("SNDLVL_55dB", SNDLVL_55dB)
        .value("SNDLVL_IDLE", SNDLVL_IDLE)
        .value("SNDLVL_60dB", SNDLVL_60dB)
        .value("SNDLVL_65dB", SNDLVL_65dB)
        .value("SNDLVL_STATIC", SNDLVL_STATIC)
        .value("SNDLVL_70dB", SNDLVL_70dB)
        .value("SNDLVL_NORM", SNDLVL_NORM)
        .value("SNDLVL_75dB", SNDLVL_75dB)
        .value("SNDLVL_80dB", SNDLVL_80dB)
        .value("SNDLVL_TALKING", SNDLVL_TALKING)
        .value("SNDLVL_85dB", SNDLVL_85dB)
        .value("SNDLVL_90dB", SNDLVL_90dB)
        .value("SNDLVL_95dB", SNDLVL_95dB)
        .value("SNDLVL_100dB", SNDLVL_100dB)
        .value("SNDLVL_105dB", SNDLVL_105dB)
        .value("SNDLVL_110dB", SNDLVL_110dB)
        .value("SNDLVL_120dB", SNDLVL_120dB)
        .value("SNDLVL_130dB", SNDLVL_130dB)
        .value("SNDLVL_GUNFIRE", SNDLVL_GUNFIRE)
        .value("SNDLVL_140dB", SNDLVL_140dB)
        .value("SNDLVL_150dB", SNDLVL_150dB)
        .value("SNDLVL_180dB", SNDLVL_180dB)
        .export_values()
        ;

    bp::class_< CSoundEnvelopeControllerHandle >( "CSoundEnvelopeController", bp::no_init )    
        .def( 
            "CheckLoopingSoundsForPlayer"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CBasePlayer * ) )( &::CSoundEnvelopeControllerHandle::CheckLoopingSoundsForPlayer )
            , ( bp::arg("pPlayer") ) )    
        .def( 
            "CommandAdd"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float,::soundcommands_t,float,float ) )( &::CSoundEnvelopeControllerHandle::CommandAdd )
            , ( bp::arg("pSound"), bp::arg("executeDeltaTime"), bp::arg("command"), bp::arg("commandTime"), bp::arg("value") ) )    
        .def( 
            "CommandClear"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::CommandClear )
            , ( bp::arg("pSound") ) )    
        .def( 
            "GetController"
            , (::CSoundEnvelopeControllerHandle (*)(  ))( &::CSoundEnvelopeControllerHandle::GetController ) )    
        .def( 
            "Play"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float,float,float ) )( &::CSoundEnvelopeControllerHandle::Play )
            , ( bp::arg("pSound"), bp::arg("volume"), bp::arg("pitch"), bp::arg("flStartTime")=0 ) )    
        .def( 
            "Shutdown"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::Shutdown )
            , ( bp::arg("pSound") ) )    
        .def( 
            "SoundChangePitch"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float,float ) )( &::CSoundEnvelopeControllerHandle::SoundChangePitch )
            , ( bp::arg("pSound"), bp::arg("pitchTarget"), bp::arg("deltaTime") ) )    
        .def( 
            "SoundChangeVolume"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float,float ) )( &::CSoundEnvelopeControllerHandle::SoundChangeVolume )
            , ( bp::arg("pSound"), bp::arg("volumeTarget"), bp::arg("deltaTime") ) )    
        .def( 
            "SoundCreate"
            , (::CSoundPatchHandle ( ::CSoundEnvelopeControllerHandle::* )( ::IRecipientFilter &,int,char const * ) )( &::CSoundEnvelopeControllerHandle::SoundCreate )
            , ( bp::arg("filter"), bp::arg("nEntIndex"), bp::arg("pSoundName") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "SoundCreate"
            , (::CSoundPatchHandle ( ::CSoundEnvelopeControllerHandle::* )( ::IRecipientFilter &,int,int,char const *,float ) )( &::CSoundEnvelopeControllerHandle::SoundCreate )
            , ( bp::arg("filter"), bp::arg("nEntIndex"), bp::arg("channel"), bp::arg("pSoundName"), bp::arg("attenuation") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "SoundCreate"
            , (::CSoundPatchHandle ( ::CSoundEnvelopeControllerHandle::* )( ::IRecipientFilter &,int,int,char const *,::soundlevel_t ) )( &::CSoundEnvelopeControllerHandle::SoundCreate )
            , ( bp::arg("filter"), bp::arg("nEntIndex"), bp::arg("channel"), bp::arg("pSoundName"), bp::arg("soundlevel") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "SoundCreate"
            , (::CSoundPatchHandle ( ::CSoundEnvelopeControllerHandle::* )( ::IRecipientFilter &,int,::EmitSound_t const & ) )( &::CSoundEnvelopeControllerHandle::SoundCreate )
            , ( bp::arg("filter"), bp::arg("nEntIndex"), bp::arg("es") )
            , bp::return_value_policy< bp::return_by_value >() )    
        .def( 
            "SoundDestroy"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::SoundDestroy )
            , ( bp::arg("pSound") ) )    
        .def( 
            "SoundFadeOut"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float,bool ) )( &::CSoundEnvelopeControllerHandle::SoundFadeOut )
            , ( bp::arg("pSound"), bp::arg("deltaTime"), bp::arg("destroyOnFadeout")=(bool)(false) ) )    
        .def( 
            "SoundGetName"
            , (::string_t ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::SoundGetName )
            , ( bp::arg("pSound") ) )    
        .def( 
            "SoundGetPitch"
            , (float ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::SoundGetPitch )
            , ( bp::arg("pSound") ) )    
        .def( 
            "SoundGetVolume"
            , (float ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle * ) )( &::CSoundEnvelopeControllerHandle::SoundGetVolume )
            , ( bp::arg("pSound") ) )    
        .def( 
            "SoundSetCloseCaptionDuration"
            , (void ( ::CSoundEnvelopeControllerHandle::* )( ::CSoundPatchHandle *,float ) )( &::CSoundEnvelopeControllerHandle::SoundSetCloseCaptionDuration )
            , ( bp::arg("pSound"), bp::arg("flDuration") ) )    
        .def( 
            "SystemReset"
            , (void ( ::CSoundEnvelopeControllerHandle::* )(  ) )( &::CSoundEnvelopeControllerHandle::SystemReset ) )    
        .def( 
            "SystemUpdate"
            , (void ( ::CSoundEnvelopeControllerHandle::* )(  ) )( &::CSoundEnvelopeControllerHandle::SystemUpdate ) )    
        .staticmethod( "GetController" );

    { //::CSoundParameters
        typedef bp::class_< CSoundParameters_wrapper > CSoundParameters_exposer_t;
        CSoundParameters_exposer_t CSoundParameters_exposer = CSoundParameters_exposer_t( "CSoundParameters", bp::init< >() );
        bp::scope CSoundParameters_scope( CSoundParameters_exposer );
        CSoundParameters_exposer.def_readwrite( "channel", &CSoundParameters::channel );
        CSoundParameters_exposer.def_readwrite( "count", &CSoundParameters::count );
        CSoundParameters_exposer.def_readwrite( "delay_msec", &CSoundParameters::delay_msec );
        CSoundParameters_exposer.def_readwrite( "pitch", &CSoundParameters::pitch );
        CSoundParameters_exposer.def_readwrite( "pitchhigh", &CSoundParameters::pitchhigh );
        CSoundParameters_exposer.def_readwrite( "pitchlow", &CSoundParameters::pitchlow );
        CSoundParameters_exposer.def_readwrite( "play_to_owner_only", &CSoundParameters::play_to_owner_only );
        CSoundParameters_exposer.def_readwrite( "soundlevel", &CSoundParameters::soundlevel );
        pyplusplus::containers::static_sized::register_array_1< char, 128 >( "__array_1_char_128" );
        { //CSoundParameters::soundname [variable], type=char[128]
        
            typedef pyplusplus::containers::static_sized::array_1_t< char, 128> ( *array_wrapper_creator )( ::CSoundParameters & );
            
            CSoundParameters_exposer.add_property( "soundname"
                , bp::make_function( array_wrapper_creator(&CSoundParameters_wrapper::pyplusplus_soundname_wrapper)
                                    , bp::with_custodian_and_ward_postcall< 0, 1 >() ) );
        }
        CSoundParameters_exposer.def_readwrite( "volume", &CSoundParameters::volume );
    }

    bp::class_< CSoundPatchHandle >( "CSoundPatch", bp::no_init );

    { //::EmitSound_t
        typedef bp::class_< EmitSound_t_wrapper, boost::noncopyable > EmitSound_exposer_t;
        EmitSound_exposer_t EmitSound_exposer = EmitSound_exposer_t( "EmitSound", bp::init< >() );
        bp::scope EmitSound_scope( EmitSound_exposer );
        EmitSound_exposer.def( bp::init< CSoundParameters const & >(( bp::arg("src") )) );
        bp::implicitly_convertible< CSoundParameters const &, EmitSound_t >();
        EmitSound_exposer.def_readwrite( "soundlevel", &EmitSound_t::m_SoundLevel );
        EmitSound_exposer.def_readwrite( "emitclosecaption", &EmitSound_t::m_bEmitCloseCaption );
        EmitSound_exposer.def_readwrite( "warnondirectwavereference", &EmitSound_t::m_bWarnOnDirectWaveReference );
        EmitSound_exposer.def_readwrite( "warnonmissingclosecaption", &EmitSound_t::m_bWarnOnMissingCloseCaption );
        EmitSound_exposer.def_readwrite( "soundtime", &EmitSound_t::m_flSoundTime );
        EmitSound_exposer.def_readwrite( "volume", &EmitSound_t::m_flVolume );
        EmitSound_exposer.def_readwrite( "soundscripthandle", &EmitSound_t::m_hSoundScriptHandle );
        EmitSound_exposer.def_readwrite( "channel", &EmitSound_t::m_nChannel );
        EmitSound_exposer.def_readwrite( "flags", &EmitSound_t::m_nFlags );
        EmitSound_exposer.def_readwrite( "pitch", &EmitSound_t::m_nPitch );
        EmitSound_exposer.def_readwrite( "speakerentity", &EmitSound_t::m_nSpeakerEntity );
        EmitSound_exposer.add_property( "origin"
                    , bp::make_function( (::Vector const * (*)( ::EmitSound_t const & ))(&EmitSound_t_wrapper::get_m_pOrigin), bp::return_internal_reference< >() )
                    , bp::make_function( (void (*)( ::EmitSound_t &,::Vector const * ))(&EmitSound_t_wrapper::set_m_pOrigin), bp::with_custodian_and_ward_postcall< 1, 2 >() ) );
    }

    bp::scope().attr( "PITCH_NORM" ) = PITCH_NORM;

    bp::scope().attr( "PITCH_LOW" ) = PITCH_LOW;

    bp::scope().attr( "PITCH_HIGH" ) = PITCH_HIGH;

    { //::PyEngineSound
        typedef bp::class_< PyEngineSound > EngineSound_exposer_t;
        EngineSound_exposer_t EngineSound_exposer = EngineSound_exposer_t( "EngineSound" );
        bp::scope EngineSound_scope( EngineSound_exposer );
        { //::PyEngineSound::GetDistGainFromSoundLevel
        
            typedef float ( ::PyEngineSound::*GetDistGainFromSoundLevel_function_type )( ::soundlevel_t,float ) ;
            
            EngineSound_exposer.def( 
                "GetDistGainFromSoundLevel"
                , GetDistGainFromSoundLevel_function_type( &::PyEngineSound::GetDistGainFromSoundLevel )
                , ( bp::arg("soundlevel"), bp::arg("dist") ) );
        
        }
        { //::PyEngineSound::GetSoundDuration
        
            typedef float ( ::PyEngineSound::*GetSoundDuration_function_type )( char const * ) ;
            
            EngineSound_exposer.def( 
                "GetSoundDuration"
                , GetSoundDuration_function_type( &::PyEngineSound::GetSoundDuration )
                , ( bp::arg("pSample") ) );
        
        }
        { //::PyEngineSound::IsSoundPrecached
        
            typedef bool ( ::PyEngineSound::*IsSoundPrecached_function_type )( char const * ) ;
            
            EngineSound_exposer.def( 
                "IsSoundPrecached"
                , IsSoundPrecached_function_type( &::PyEngineSound::IsSoundPrecached )
                , ( bp::arg("pSample") ) );
        
        }
        { //::PyEngineSound::NotifyBeginMoviePlayback
        
            typedef void ( ::PyEngineSound::*NotifyBeginMoviePlayback_function_type )(  ) ;
            
            EngineSound_exposer.def( 
                "NotifyBeginMoviePlayback"
                , NotifyBeginMoviePlayback_function_type( &::PyEngineSound::NotifyBeginMoviePlayback ) );
        
        }
        { //::PyEngineSound::NotifyEndMoviePlayback
        
            typedef void ( ::PyEngineSound::*NotifyEndMoviePlayback_function_type )(  ) ;
            
            EngineSound_exposer.def( 
                "NotifyEndMoviePlayback"
                , NotifyEndMoviePlayback_function_type( &::PyEngineSound::NotifyEndMoviePlayback ) );
        
        }
        { //::PyEngineSound::PrecacheSentenceGroup
        
            typedef void ( ::PyEngineSound::*PrecacheSentenceGroup_function_type )( char const * ) ;
            
            EngineSound_exposer.def( 
                "PrecacheSentenceGroup"
                , PrecacheSentenceGroup_function_type( &::PyEngineSound::PrecacheSentenceGroup )
                , ( bp::arg("pGroupName") ) );
        
        }
        { //::PyEngineSound::PrecacheSound
        
            typedef bool ( ::PyEngineSound::*PrecacheSound_function_type )( char const *,bool,bool ) ;
            
            EngineSound_exposer.def( 
                "PrecacheSound"
                , PrecacheSound_function_type( &::PyEngineSound::PrecacheSound )
                , ( bp::arg("pSample"), bp::arg("bPreload")=(bool)(false), bp::arg("bIsUISound")=(bool)(false) ) );
        
        }
        { //::PyEngineSound::PrefetchSound
        
            typedef void ( ::PyEngineSound::*PrefetchSound_function_type )( char const * ) ;
            
            EngineSound_exposer.def( 
                "PrefetchSound"
                , PrefetchSound_function_type( &::PyEngineSound::PrefetchSound )
                , ( bp::arg("pSample") ) );
        
        }
        { //::PyEngineSound::StopSound
        
            typedef void ( ::PyEngineSound::*StopSound_function_type )( int,int,char const * ) ;
            
            EngineSound_exposer.def( 
                "StopSound"
                , StopSound_function_type( &::PyEngineSound::StopSound )
                , ( bp::arg("iEntIndex"), bp::arg("iChannel"), bp::arg("pSample") ) );
        
        }
        }bp::scope().attr( "soundengine" ) = boost::ref(pysoundengine);{
    }
}
#endif

