#include "Module_Menu_Game_Mode.h"

// AModule_Menu_Game_Mode
AAModule_Menu_Game_Mode::AAModule_Menu_Game_Mode()
{
	Module_Widgets.Init(0, 6);  // Create 6 ptrs = 0;
}
//-----------------------------------------------------------------------------------------------------------
void AAModule_Menu_Game_Mode::BeginPlay()
{
	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
void AAModule_Menu_Game_Mode::Create_Menu_Main()
{
	UAModule_Menu_Main *module_menu_widget = 0;
	APlayerController *player_controller = 0;
	FInputModeUIOnly input_mode_ui_only {};
	
	player_controller = GetWorld()->GetFirstPlayerController();
	player_controller->SetShowMouseCursor(true);
	player_controller->SetInputMode(input_mode_ui_only);

	// Create Menu Main
	module_menu_widget = CreateWidget<UAModule_Menu_Main>(player_controller, Module_Widgets[0]);
	module_menu_widget->Buttons_Menu_Init(New_Game_Level_Open_Name, Module_Widgets[1], Module_Widgets[2], Module_Widgets[3], Module_Widgets[4], Module_Widgets[5]);
	module_menu_widget->AddToViewport();
}
//-----------------------------------------------------------------------------------------------------------
