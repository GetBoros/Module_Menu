#include "Module_Menu_Config.h"
#include <Internationalization/Text.h>

// AsModule_Menu_Config
UGameUserSettings *AsModule_Menu_Config::User_Settings = 0;
const FIntPoint AsModule_Menu_Config::Screen_Resolution_Array[AsModule_Menu_Config::Button_Setting_Count] = { {960, 540}, {1280, 720}, {1920, 1080}, {2560, 1440}, {3840, 2160} };
const FName AsModule_Menu_Config::Button_Name_Defaults[Button_Setting_Count] = { L"1", L"2", L"3", L"4", L"5" };
//------------------------------------------------------------------------------------------------------------
#define LOCTEXT_NAMESPACE "AsModule_Menu_Config"
//------------------------------------------------------------------------------------------------------------
const FText AsModule_Menu_Config::Get_Localization_Text_Menu_Main(const EModule_Menu_Main_Button_State menu_main_button_index)
{
    switch (menu_main_button_index)
    {
    case EModule_Menu_Main_Button_State::New_Game:
        return LOCTEXT("ExampleText0", "New Game");
    case EModule_Menu_Main_Button_State::Continue:
        return LOCTEXT("ExampleText1", "Continues");
    case EModule_Menu_Main_Button_State::Settings:
        return LOCTEXT("ExampleText2", "Options");
    case EModule_Menu_Main_Button_State::Arsenals:
        return LOCTEXT("ExampleText4", "Arsenal");
    case EModule_Menu_Main_Button_State::Achivments:
        return LOCTEXT("ExampleText3", "Achievements");
    case EModule_Menu_Main_Button_State::Exit:
        return LOCTEXT("ExampleText5", "Exit Game");
    default:
        return LOCTEXT("InvalidText", "Invalid index");
    }
}
//------------------------------------------------------------------------------------------------------------
const FText AsModule_Menu_Config::Get_Localization_Text_Menu_Option(const EModule_Menu_Option_Button_Tabs menu_main_button_index)
{
    switch (menu_main_button_index)
    {
    case EModule_Menu_Option_Button_Tabs::Graphics:
        return LOCTEXT("Graphics_0", "Graphics");
    case EModule_Menu_Option_Button_Tabs::Gameplay:
        return LOCTEXT("Gameplay_1", "Gameplay");
    case EModule_Menu_Option_Button_Tabs::Keyboard:
        return LOCTEXT("Keyboard_2", "Keyboard");
    case EModule_Menu_Option_Button_Tabs::Mouse:
        return LOCTEXT("Mouse_3", "Mouse");
    case EModule_Menu_Option_Button_Tabs::Audio:
        return LOCTEXT("Audio_4", "Audio");
    default:
        return LOCTEXT("InvalidText", "Invalid index");
    }
}
//------------------------------------------------------------------------------------------------------------
const FText AsModule_Menu_Config::Get_Localization_Text_Slider_State_Window(const int slider_window_state)
{
    switch (slider_window_state)
    {
    case 0:
        return LOCTEXT("FullScreen_0", "FullScreen");
    case 1:
        return LOCTEXT("WFullScreen_0", "WFullScreen");
    case 2:
        return LOCTEXT("Windowed_0", "Windowed");
    default:
        return LOCTEXT("InvalidText", "Invalid index");
    }
}
//------------------------------------------------------------------------------------------------------------
const FText AsModule_Menu_Config::Get_Localization_Text_Slider_State_Default(const int button_setting_count)
{
    switch (button_setting_count)
    {
    case 0:
        return LOCTEXT("Lowest_0", "Lowest");
    case 1:
        return LOCTEXT("Middle_0", "Middle");
    case 2:
        return LOCTEXT("Hight_0", "Hight");
    case 3:
        return LOCTEXT("Epic_0", "Epic");
    case 4:
        return LOCTEXT("Cinematic_0", "Cinematic");
    default:
        return LOCTEXT("InvalidText", "Invalid index");
    }
}
//------------------------------------------------------------------------------------------------------------
const FText AsModule_Menu_Config::Get_Localization_Text_Slider_State_Custom(const int button_setting_count)
{
    switch (button_setting_count)
    {
    case 0:
        return LOCTEXT("Lowest_2", "Unhandled");
    case 1:
        return LOCTEXT("Middle_2", "Custom");
    case 2:
        return LOCTEXT("Hight_2", "Hidden");
    case 3:
        return LOCTEXT("Epic_2", "Showed");
    default:
        return LOCTEXT("InvalidText", "Invalid index");
    }
}
//------------------------------------------------------------------------------------------------------------
const FText AsModule_Menu_Config::Get_Localization_Text_Tab_Button_Name(const EOption_Type button_type)
{
    switch (button_type)
    {
    case EOption_Type::EPT_Quality_Presset:
        return LOCTEXT("Quality Presset", "Quality Presset : ");
    case EOption_Type::EPT_Quality_Shadows:
        return LOCTEXT("Shadows", "Shadows : ");
    case EOption_Type::EPT_Quality_Foliage:
        return LOCTEXT("Foliage", "Foliage : ");
    case EOption_Type::EPT_Quality_Texture:
        return LOCTEXT("Texture", "Texture : ");
    case EOption_Type::EPT_Quality_Shading:
        return LOCTEXT("Shading", "Shading : ");
    case EOption_Type::EPT_Quality_Reflection:
        return LOCTEXT("Reflection", "Reflection : ");
    case EOption_Type::EPT_Quality_Anti_Aliasing:
        return LOCTEXT("Anti Aliasing", "Anti Aliasing : ");
    case EOption_Type::EPT_Quality_Visual_Effects:
        return LOCTEXT("Visual Effects", "Visual Effects : ");
    case EOption_Type::EPT_Quality_View_Distances:
        return LOCTEXT("View Distances", "View Distances : ");
    case EOption_Type::EPT_Quality_Post_Processing:
        return LOCTEXT("Post Processing", "Post Processing : ");
    case EOption_Type::EPT_Quality_Global_Illumination_Quality:
        return LOCTEXT("Global Illumination", "Global Illumination : ");
    case EOption_Type::EPT_Window_Mode:
        return LOCTEXT("Window Mode", "Window Mode : ");
    case EOption_Type::EPT_Frame_Rate:
        return LOCTEXT("Frame Rate", "Frame Rate : ");
    case EOption_Type::EPT_Screen_Resolution:
        return LOCTEXT("Screen Resolution", "Screen Resolution : ");
    case EOption_Type::EPT_Screen_Percentage:
        return LOCTEXT("Screen Percentage ", "Screen Percentage  : ");
    case EOption_Type::EPT_DirectX_Switcher:
        return LOCTEXT("Toogle Directx", "Toogle Directx : ");
    case EOption_Type::EPT_Show_Frame_Per_Sec:
        return LOCTEXT("Show FPS", "Show FPS : ");
    default:
        return LOCTEXT("EOption_Type Invalid", "Invalid index EOption_Type");
    }
}
//------------------------------------------------------------------------------------------------------------
#undef LOCTEXT_NAMESPACE
//------------------------------------------------------------------------------------------------------------
const void AsModule_Menu_Config::Throw()
{
	return throw 13;
}
//------------------------------------------------------------------------------------------------------------
