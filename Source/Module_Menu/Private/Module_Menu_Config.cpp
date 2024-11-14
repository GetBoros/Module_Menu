#include "Module_Menu_Config.h"

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
#undef LOCTEXT_NAMESPACE
//------------------------------------------------------------------------------------------------------------
void AsModule_Menu_Config::Throw()
{
	return throw 13;
}
//------------------------------------------------------------------------------------------------------------




