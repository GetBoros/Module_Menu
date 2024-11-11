#include "Module_Menu_Config.h"

// AsModule_Menu_Config
const FIntPoint AsModule_Menu_Config::Screen_Resolution_Array[AsModule_Menu_Config::Button_Setting_Count] = { {960, 540}, {1280, 720}, {1920, 1080}, {2560, 1440}, {3840, 2160} };
const FName AsModule_Menu_Config::Button_Name_Defaults[Button_Setting_Count] = { L"1", L"2", L"3", L"4", L"5" };
//------------------------------------------------------------------------------------------------------------
#define LOCTEXT_NAMESPACE "AsModule_Menu_Config"
//------------------------------------------------------------------------------------------------------------
const FText AsModule_Menu_Config::Get_Menu_Main_Text(const EModule_Menu_Main_Button_State menu_main_button_index)
{
    TArray<FText> Examples = {
        LOCTEXT("ExampleText0", "New Game"),
        LOCTEXT("ExampleText1", "Continues"),
        LOCTEXT("ExampleText2", "Options"),
        LOCTEXT("ExampleText3", "Achievements"),
        LOCTEXT("ExampleText4", "Arsenal"),
        LOCTEXT("ExampleText5", "Exit Game")
    };

    switch (menu_main_button_index)
    {
    case EModule_Menu_Main_Button_State::Count:
        return LOCTEXT("InvalidText", "Invalid index");
        break;
    default:
        return Examples[(int)menu_main_button_index];
        break;
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




