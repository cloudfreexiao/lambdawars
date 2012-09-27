//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include <stdio.h>

#include <vgui/IBorder.h>
#include <vgui/ISurface.h>
#include <vgui/IScheme.h>
#include <vgui/IBorder.h>
#include <KeyValues.h>

#include <vgui_controls/ImagePanel.h>
#include <vgui_controls/Image.h>
#include <vgui_controls/Controls.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

DECLARE_BUILD_FACTORY( ImagePanel );

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
ImagePanel::ImagePanel(Panel *parent, const char *name) : Panel(parent, name)
{
	m_pImage = NULL;
	m_pszImageName = NULL;
	m_pszFillColorName = NULL;
	m_pszDrawColorName = NULL;
	m_bScaleImage = false;
	m_bTileImage = false;
	m_bTileHorizontally = false;
	m_bTileVertically = false;
	m_fScaleAmount = 0.0f;
	m_FillColor = Color(0, 0, 0, 0);
	m_DrawColor = Color(255,255,255,255);
	m_iFrame = 0;

	SetImage(m_pImage);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
ImagePanel::~ImagePanel()
{
	delete [] m_pszImageName;
	delete [] m_pszFillColorName;
	delete [] m_pszDrawColorName;
}

//-----------------------------------------------------------------------------
// Purpose: handles size changing
//-----------------------------------------------------------------------------
void ImagePanel::OnSizeChanged(int newWide, int newTall)
{
	BaseClass::OnSizeChanged(newWide, newTall);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void ImagePanel::SetImage(IImage *image)
{
	m_pImage = image;
	Repaint();
}

//-----------------------------------------------------------------------------
// Purpose: sets an image by file name
//-----------------------------------------------------------------------------
void ImagePanel::SetImage(const char *imageName)
{
	int len = Q_strlen(imageName) + 1;
	delete [] m_pszImageName;
	m_pszImageName = new char[ len ];
	Q_strncpy(m_pszImageName, imageName, len );
	InvalidateLayout(false, true); // forrce applyschemesettings to run
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
IImage *ImagePanel::GetImage()
{
	return m_pImage;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
Color ImagePanel::GetDrawColor( void )
{
	return m_DrawColor;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void ImagePanel::SetDrawColor( Color drawColor )
{
	m_DrawColor = drawColor;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void ImagePanel::PaintBackground()
{
	if (m_FillColor[3] > 0)
	{
		// draw the specified fill color
		int wide, tall;
		GetSize(wide, tall);
		surface()->DrawSetColor(m_FillColor);
		surface()->DrawFilledRect(0, 0, wide, tall);
	}
	if (m_pImage)
	{
		surface()->DrawSetColor( 255, 255, 255, 255 );
		m_pImage->SetPos(0, 0);

		if (m_bScaleImage)
		{
			// Image size is stored in the bitmap, so temporarily set its size
			// to our panel size and then restore after we draw it.

			int imageWide, imageTall;
			m_pImage->GetSize( imageWide, imageTall );

			if ( m_fScaleAmount > 0.0f )
			{
				float wide, tall;
				wide = static_cast<float>(imageWide) * m_fScaleAmount;
				tall = static_cast<float>(imageTall) * m_fScaleAmount;
				m_pImage->SetSize( static_cast<int>(wide), static_cast<int>(tall) );
			}
			else
			{
				int wide, tall;
				GetSize( wide, tall );
				m_pImage->SetSize( wide, tall );
			}

			m_pImage->SetColor( GetDrawColor() );
			m_pImage->Paint();

			m_pImage->SetSize( imageWide, imageTall );
		}
		else if ( m_bTileImage || m_bTileHorizontally || m_bTileVertically )
		{
			int wide, tall;
			GetSize(wide, tall);
			int imageWide, imageTall;
			m_pImage->GetSize( imageWide, imageTall );

			int y = 0;
			while ( y < tall )
			{
				int x = 0;
				while (x < wide)
				{
					m_pImage->SetPos(x,y);
					m_pImage->Paint();

					x += imageWide;

					if ( !m_bTileHorizontally )
						break;
				}

				y += imageTall;

				if ( !m_bTileVertically )
					break;
			}
			m_pImage->SetPos(0, 0);
		}
		else
		{
			m_pImage->Paint();
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Gets control settings for editing
//-----------------------------------------------------------------------------
void ImagePanel::GetSettings(KeyValues *outResourceData)
{
	BaseClass::GetSettings(outResourceData);
	if (m_pszImageName)
	{
		outResourceData->SetString("image", m_pszImageName);
	}
	if (m_pszFillColorName)
	{
		outResourceData->SetString("fillcolor", m_pszFillColorName);
	}
	if (GetBorder())
	{
		outResourceData->SetString("border", GetBorder()->GetName());
	}

	outResourceData->SetInt("scaleImage", m_bScaleImage);
	outResourceData->SetFloat("scaleAmount", m_fScaleAmount);
	outResourceData->SetInt("tileImage", m_bTileImage);
	outResourceData->SetInt("tileHorizontally", m_bTileHorizontally);
	outResourceData->SetInt("tileVertically", m_bTileVertically);
}

//-----------------------------------------------------------------------------
// Purpose: Applies designer settings from res file
//-----------------------------------------------------------------------------
void ImagePanel::ApplySettings(KeyValues *inResourceData)
{
	delete [] m_pszImageName;
	delete [] m_pszFillColorName;
	m_pszImageName = NULL;
	m_pszFillColorName = NULL;

	m_bScaleImage = inResourceData->GetInt("scaleImage", 0);
	m_fScaleAmount = inResourceData->GetFloat("scaleAmount", 0.0f);
	m_bTileImage = inResourceData->GetInt("tileImage", 0);
	m_bTileHorizontally = inResourceData->GetInt("tileHorizontally", m_bTileImage);
	m_bTileVertically = inResourceData->GetInt("tileVertically", m_bTileImage);
	const char *imageName = inResourceData->GetString("image", "");
	if (*imageName)
	{
		SetImage( imageName );
	}

	const char *pszFillColor = inResourceData->GetString("fillcolor", "");
	if (*pszFillColor)
	{
		int r = 0, g = 0, b = 0, a = 255;
		int len = Q_strlen(pszFillColor) + 1;
		m_pszFillColorName = new char[ len ];
		Q_strncpy( m_pszFillColorName, pszFillColor, len );

		if (sscanf(pszFillColor, "%d %d %d %d", &r, &g, &b, &a) >= 3)
		{
			// it's a direct color
			m_FillColor = Color(r, g, b, a);
		}
		else
		{
			IScheme *pScheme = scheme()->GetIScheme( GetScheme() );
			m_FillColor = pScheme->GetColor(pszFillColor, Color(0, 0, 0, 0));
		}
	}

	const char *pszBorder = inResourceData->GetString("border", "");
	if (*pszBorder)
	{
		IScheme *pScheme = scheme()->GetIScheme( GetScheme() );
		SetBorder(pScheme->GetBorder(pszBorder));
	}

	BaseClass::ApplySettings(inResourceData);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool ImagePanel::EvictImage()
{
	if( !m_pImage )
		return false;
	return m_pImage->Evict();
}
	
int ImagePanel::GetNumFrames()
{
	if( m_pImage )
		return m_pImage->GetNumFrames();
	return 0;
}

void ImagePanel::SetFrame( int nFrame )
{
	m_iFrame = nFrame;
	if( m_pImage )
		m_iFrame = MIN( MAX( 0, m_iFrame), m_pImage->GetNumFrames() );
}

int ImagePanel::GetFrame() const
{
	if( m_pImage )
		return MIN( MAX( 0, m_iFrame), m_pImage->GetNumFrames() );
	return m_iFrame;
}

//-----------------------------------------------------------------------------
// Purpose:  load the image, this is done just before this control is displayed
//-----------------------------------------------------------------------------
void ImagePanel::ApplySchemeSettings( IScheme *pScheme )
{
	BaseClass::ApplySchemeSettings(pScheme);
	if ( m_pszImageName && strlen( m_pszImageName ) > 0 )
	{
		SetImage(scheme()->GetImage(m_pszImageName, m_bScaleImage));
	}
}

//-----------------------------------------------------------------------------
// Purpose: Describes editing details
//-----------------------------------------------------------------------------
const char *ImagePanel::GetDescription()
{
	static char buf[1024];
	_snprintf(buf, sizeof(buf), "%s, string image, string border, string fillcolor, bool scaleImage", BaseClass::GetDescription());
	return buf;
}

//-----------------------------------------------------------------------------
// Purpose: sets whether or not the image should scale to fit the size of the ImagePanel (defaults to false)
//-----------------------------------------------------------------------------
void ImagePanel::SetShouldScaleImage( bool state )
{
	m_bScaleImage = state;
}

//-----------------------------------------------------------------------------
// Purpose: used in conjunction with setting that the image should scale and defines an absolute scale amount
//-----------------------------------------------------------------------------
void ImagePanel::SetScaleAmount( float scale )
{
	m_fScaleAmount = scale;
}

float ImagePanel::GetScaleAmount( void )
{
	return m_fScaleAmount;
}

//-----------------------------------------------------------------------------
// Purpose: set the color to fill with, if no Image is specified
//-----------------------------------------------------------------------------
void ImagePanel::SetFillColor( Color col )
{
	m_FillColor = col;
}

//-----------------------------------------------------------------------------
// Purpose: data accessor
//-----------------------------------------------------------------------------
Color ImagePanel::GetFillColor()
{
	return m_FillColor;
}

char *ImagePanel::GetImageName()
{
	return m_pszImageName;
}
