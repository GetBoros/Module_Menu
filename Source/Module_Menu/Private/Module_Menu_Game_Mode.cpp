#include "Module_Menu_Game_Mode.h"

// AModule_Menu_Game_Mode
void AAModule_Menu_Game_Mode::BeginPlay()
{

	Super::BeginPlay();
}
//-----------------------------------------------------------------------------------------------------------
void AAModule_Menu_Game_Mode::Create_Menu_Main(FName level, TSubclassOf<UUserWidget> m_main, TSubclassOf<UUserWidget> m_button,
	TSubclassOf<UUserWidget> m_option, TSubclassOf<UUserWidget> m_o_button, TSubclassOf<UUserWidget> m_o_tab, TSubclassOf<UUserWidget> m_o_tab_button)
{
	UAModule_Menu_Main *module_menu_widget = 0;
	APlayerController *player_controller = 0;
	FInputModeUIOnly input_mode_ui_only;
	
	player_controller = GetWorld()->GetFirstPlayerController();
	player_controller->SetShowMouseCursor(true);
	player_controller->SetInputMode(input_mode_ui_only);

	// Create Menu Main
	module_menu_widget = CreateWidget<UAModule_Menu_Main>(player_controller, m_main);
	module_menu_widget->AddToViewport();
	module_menu_widget->Buttons_Menu_Init(level, m_button, m_option, m_o_button, m_o_tab, m_o_tab_button);
}
//-----------------------------------------------------------------------------------------------------------
