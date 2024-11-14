#include "Module_Menu_Game_Mode.h"

// AModule_Menu_Game_Mode
AAModule_Menu_Game_Mode::AAModule_Menu_Game_Mode()
{
	Module_Widgets.Init(0, (int)EModule_Menu_Widget_Type::WT_Count);  // Create 6 ptrs at UUSerWidget
}
//-----------------------------------------------------------------------------------------------------------
void AAModule_Menu_Game_Mode::Create_Menu_Main()
{
	UAModule_Menu_Main *module_menu_widget = 0;
	APlayerController *player_controller = 0;
	FInputModeUIOnly input_mode_ui_only {};

	// Or make in one func?
	AsModule_Menu_Config::User_Settings = GEngine->GetGameUserSettings();
	AsModule_Menu_Config::User_Settings->LoadSettings();
	AsModule_Menu_Config::User_Settings->ApplySettings(false);

	player_controller = GetWorld()->GetFirstPlayerController();
	player_controller->SetShowMouseCursor(true);
	player_controller->SetInputMode(input_mode_ui_only);

	// Create Menu Main
	module_menu_widget = CreateWidget<UAModule_Menu_Main>(player_controller, Module_Widgets[(int)EModule_Menu_Widget_Type::WT_Main]);
	module_menu_widget->Buttons_Menu_Setup(New_Game_Level_Open_Name, Module_Widgets);
	module_menu_widget->AddToViewport();
}
//-----------------------------------------------------------------------------------------------------------
