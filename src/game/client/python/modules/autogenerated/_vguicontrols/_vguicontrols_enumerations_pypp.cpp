// This file has been generated by Py++.

#include "cbase.h"
#include "cbase.h"
#include "vgui_controls/Panel.h"
#include "vgui_controls/AnimationController.h"
#include "vgui_controls/EditablePanel.h"
#include "vgui_controls/AnalogBar.h"
#include "vgui_controls/Image.h"
#include "vgui_controls/TextImage.h"
#include "vgui_controls/ScrollBar.h"
#include "vgui_controls/ScrollBarSlider.h"
#include "vgui_controls/Menu.h"
#include "vgui_controls/MenuButton.h"
#include "vgui_controls/Frame.h"
#include "vgui_controls/TextEntry.h"
#include "vgui_controls/RichText.h"
#include "vgui_controls/Tooltip.h"
#include "vgui/IBorder.h"
#include "vgui_bitmapimage.h"
#include "vgui_avatarimage.h"
#include "srcpy_vgui.h"
#include "hl2wars/hl2wars_baseminimap.h"
#include "hl2wars/vgui_video_general.h"
#include "hl2wars/vgui/wars_model_panel.h"
#include "srcpy.h"
#include "tier0/memdbgon.h"
#include "_vguicontrols_enumerations_pypp.hpp"

namespace bp = boost::python;

void _vguicontrols_register_enumerations(){

    bp::enum_< EAvatarSize>("EAvatarSize")
        .value("k_EAvatarSize32x32", k_EAvatarSize32x32)
        .value("k_EAvatarSize64x64", k_EAvatarSize64x64)
        .value("k_EAvatarSize184x184", k_EAvatarSize184x184)
        .export_values()
        ;

}
