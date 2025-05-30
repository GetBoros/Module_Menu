#include "Module_Menu_Main.h"
#include "Module_Menu.h"
#include "Components/Button.h"



// UAModule_Menu_Option_Button_Switcher
UAModule_Menu_Option_Button_Switcher *UAModule_Menu_Option_Button_Switcher::Button_Previous = 0;
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Option_Button_Switcher::Create_Button(const int button_index, UWidgetSwitcher *widget_switcher)
{
	WidgetSwitcher_Tab = widget_switcher;
	Button_Switcher_State_Index = (EModule_Menu_Option_Button_Tabs)button_index;

	Button_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Menu_Option((EModule_Menu_Option_Button_Tabs)button_index) );  // Set button name
	Button_Hitbox->OnPressed.AddDynamic(this, &UAModule_Menu_Option_Button_Switcher::Button_Pressed);
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Option_Button_Switcher::Button_Pressed()
{
	Button_Previous->Button_Hitbox->SetBackgroundColor(AsModule_Menu_Config::Button_Inactive);  // Redraw prev button to inactive
	Button_Previous = this;  // not this button is previous
	Button_Hitbox->SetBackgroundColor(AsModule_Menu_Config::Button_Active);  // Draw this button as active
	WidgetSwitcher_Tab->SetActiveWidgetIndex( (int)Button_Switcher_State_Index);  // Switch Tab
}
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Tab_Button
void UAModule_Menu_Tab_Button::Button_Setting_Setup()
{
	Get_Tab_Buttons_Settings();  // Initialize

	Button_Slider->OnValueChanged.AddDynamic(this, &UAModule_Menu_Tab_Button::Button_Slider_Value_Changed);  // What to do if pressed on button
	Button_Slider->OnMouseCaptureEnd.AddDynamic(this, &UAModule_Menu_Tab_Button::Settings_Apply);
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Get_Tab_Buttons_Settings()
{
	int i = 0;
	float slider_value = 0.0f;
	float slider_step_size = 1.0f;
	float slider_min_value = 0.0f;
	float slider_max_value = 4.0f;
	FIntPoint int_point {};
	FString slider_text_value {};  // Used to update Slider Text Block

	Button_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Tab_Button_Name(Button_Tab_Type) );  // Button Name

	switch (Button_Tab_Type)
	{// For current button type have unique button setting || Get Setting to an apply it || And Limiting Sliders for unique settings

	case EOption_Type::EPT_Quality_Presset:
		slider_value = AsModule_Menu_Config::User_Settings->GetOverallScalabilityLevel();
		break;
	case EOption_Type::EPT_Quality_Shadows:
		slider_value = AsModule_Menu_Config::User_Settings->GetShadowQuality();
		break;
	case EOption_Type::EPT_Quality_Foliage:
		slider_value = AsModule_Menu_Config::User_Settings->GetFoliageQuality();
		break;
	case EOption_Type::EPT_Quality_Texture:
		slider_value = AsModule_Menu_Config::User_Settings->GetTextureQuality();
		break;
	case EOption_Type::EPT_Quality_Shading:
		slider_value = AsModule_Menu_Config::User_Settings->GetShadingQuality();
		break;
	case EOption_Type::EPT_Quality_Reflection:
		slider_value = AsModule_Menu_Config::User_Settings->GetReflectionQuality();
		break;
	case EOption_Type::EPT_Quality_Anti_Aliasing:
		slider_value = AsModule_Menu_Config::User_Settings->GetAntiAliasingQuality();
		break;
	case EOption_Type::EPT_Quality_Visual_Effects:
		slider_value = AsModule_Menu_Config::User_Settings->GetVisualEffectQuality();
		break;
	case EOption_Type::EPT_Quality_View_Distances:
		slider_value = AsModule_Menu_Config::User_Settings->GetViewDistanceQuality();
		break;
	case EOption_Type::EPT_Quality_Post_Processing:
		slider_value = AsModule_Menu_Config::User_Settings->GetPostProcessingQuality();
		break;
	case EOption_Type::EPT_Quality_Global_Illumination_Quality:
		slider_value = AsModule_Menu_Config::User_Settings->GetGlobalIlluminationQuality();
		break;
	case EOption_Type::EPT_Window_Mode:
		slider_value = AsModule_Menu_Config::User_Settings->GetFullscreenMode();
		Slider_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Slider_State_Window(slider_value) );
		slider_max_value = 2.0f;
		break;
	case EOption_Type::EPT_Frame_Rate:
		slider_min_value = 24.0f;
		slider_max_value = 144.0f;
		slider_value = FMath::Clamp(AsModule_Menu_Config::User_Settings->GetFrameRateLimit(), slider_min_value, slider_max_value);
		Slider_Text_Block->SetText(FText::FromString(FString::FromInt(slider_value) ) );
		break;
	case EOption_Type::EPT_Screen_Resolution:  // Fix those
		int_point = AsModule_Menu_Config::User_Settings->GetScreenResolution();
		for (i = 0; i < AsModule_Menu_Config::Button_Setting_Count; i++)  // Find current screen resolution | need to redraw current setting
			if (AsModule_Menu_Config::Screen_Resolution_Array[i] == int_point)
				slider_value = i;
		Slider_Text_Block->SetText(FText::FromString(AsModule_Menu_Config::Slider_State_Resolution[(int)slider_value]) );
		break;
	case EOption_Type::EPT_Screen_Percentage:
		slider_min_value = 0.3f;
		slider_step_size = 0.1f;
		slider_max_value = 1.0f;
		slider_value = FMath::Clamp(AsModule_Menu_Config::User_Settings->GetResolutionScaleNormalized(), slider_min_value, slider_max_value);
		Slider_Text_Block->SetText(FText::FromString(FString::FromInt( (int)(slider_value * 100.0f) ) ) );
		break;
	case EOption_Type::EPT_DirectX_Switcher:
		GConfig->GetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), slider_text_value, FPaths::ProjectConfigDir() + TEXT("DefaultEngine.ini") );
		Slider_Text_Block->SetText(FText::FromString(slider_text_value.Right(4) ) );  // 4 - Last 4 chars || Must Be DX12 or DX11
		slider_max_value = 1.0f;
		slider_value = slider_text_value.Right(4) == L"DX12" ? 1 : 0;
		break;
	case EOption_Type::EPT_Show_Frame_Per_Sec:
		Slider_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Slider_State_Custom( (int)ESlider_Text_State::Toogle) );
		slider_max_value = 1.0f;
		break;
	}
	
	Button_Slider->MouseUsesStep = true;  // floor or clamp effect | offset to stepsize
	Button_Slider->SetMinValue(slider_min_value);
	Button_Slider->SetStepSize(slider_step_size);
	Button_Slider->SetMaxValue(slider_max_value);  // Max setting when 4 is Cinematic and 0 is lowest quality
	Button_Slider->SetValue(slider_value);  // Apply slider settings

	if (slider_value == -1.0f)  // If presset is custom show it
		Slider_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Slider_State_Custom( (int)ESlider_Text_State::Custom_Settings) );
	
	if (Button_Tab_Type < EOption_Type::EPT_Graphic_Last)  // Handle quality settings other is unique
		Slider_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Slider_State_Default(slider_value) );
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Set_Tab_Buttons_Settings(const float changed_value)
{
	const float ceiled_value = FMath::CeilToFloat(changed_value * 10.0f) / 10.0f;

	switch (Button_Tab_Type)
	{
	case EOption_Type::EPT_Quality_Presset:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetOverallScalabilityLevel(ceiled_value);
		Tab_Buttons_Quality_Redraw();
		break;
	case EOption_Type::EPT_Quality_Shadows:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetShadowQuality(ceiled_value);
		break;
	case EOption_Type::EPT_Quality_Foliage:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetFoliageQuality(ceiled_value);
		break;
	case EOption_Type::EPT_Quality_Texture:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetTextureQuality(ceiled_value);
		break;
	case EOption_Type::EPT_Quality_Shading:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetShadingQuality(ceiled_value);
		break;
	case EOption_Type::EPT_Quality_Reflection:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetReflectionQuality(ceiled_value);
		break;
	case EOption_Type::EPT_Quality_Anti_Aliasing:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetAntiAliasingQuality(ceiled_value);
		break;
	case EOption_Type::EPT_Quality_Visual_Effects:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetVisualEffectQuality(ceiled_value);
		break;
	case EOption_Type::EPT_Quality_View_Distances:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetViewDistanceQuality(ceiled_value);
		break;
	case EOption_Type::EPT_Quality_Post_Processing:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetPostProcessingQuality(ceiled_value);
		break;
	case EOption_Type::EPT_Quality_Global_Illumination_Quality:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetGlobalIlluminationQuality(ceiled_value);
		break;
	case EOption_Type::EPT_Graphic_Last:
		break;
	case EOption_Type::EPT_Window_Mode:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetFullscreenMode(EWindowMode::ConvertIntToWindowMode( (int)ceiled_value) );
		Slider_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Slider_State_Window( (int)ceiled_value) );
		break;
	case EOption_Type::EPT_Frame_Rate:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetFrameRateLimit(ceiled_value);
		Slider_Text_Block->SetText(FText::FromString(FString::FromInt(ceiled_value) ) );
		break;
	case EOption_Type::EPT_Screen_Resolution:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetScreenResolution(AsModule_Menu_Config::Screen_Resolution_Array[(int)ceiled_value]);
		Slider_Text_Block->SetText(FText::FromString(AsModule_Menu_Config::Slider_State_Resolution[(int)ceiled_value]) );
		break;
	case EOption_Type::EPT_Screen_Percentage:
		AsModule_Menu_Config::AsModule_Menu_Config::User_Settings->SetResolutionScaleNormalized(ceiled_value);
		Slider_Text_Block->SetText(FText::FromString(FString::FromInt( (int)(ceiled_value * 100.0f) ) ) );
		break;
	case EOption_Type::EPT_DirectX_Switcher:
		DirectX_Switcher();
		Slider_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Slider_State_Custom( (int)ESlider_Text_State::Toogled) );
		break;
	case EOption_Type::EPT_Show_Frame_Per_Sec:
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("stat fps") );  // Exit from game
		Slider_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Slider_State_Custom( (int)ESlider_Text_State::Toogled) );
		break;
	case EOption_Type::EPT_Last:
		break;
	default:
		AsModule_Menu_Config::Throw();
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Set_Slider_Text_Block(const int button_index)
{
	if (EOption_Type::EPT_Graphic_Last > Button_Tab_Type)  // Handle quality settings other is unique
		if (button_index == -1)  // If presset is custom show it
			Slider_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Slider_State_Custom((int)ESlider_Text_State::Custom_Settings) );
		else
			Slider_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Slider_State_Default( (int)button_index) );
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Tab_Buttons_Quality_Redraw() const
{
	TArray<UWidget *> parent_childs = GetParent() -> GetAllChildren();
	UAModule_Menu_Tab_Button *module_menu_tab_button = 0;

	for (UWidget *&parent_child : parent_childs)
	{
		module_menu_tab_button = Cast<UAModule_Menu_Tab_Button>(parent_child);
		if (module_menu_tab_button != 0)
		{
			module_menu_tab_button->Get_Tab_Buttons_Settings();  // In WBP called parent cast to and update setting
			if (module_menu_tab_button->Button_Tab_Type == (EOption_Type)( (int)EOption_Type::EPT_Graphic_Last - 1) )  // If not Graphics setting quit
				return;
		}
	}
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::DirectX_Switcher() const
{
	FString config_path = FPaths::ProjectConfigDir() + TEXT("DefaultEngine.ini");
    FString current_rhi;

    if (GConfig->GetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), current_rhi, config_path) )  // Get current DXT
        if (current_rhi == TEXT("DefaultGraphicsRHI_DX12") )  // Toogle DX
            GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), TEXT("DefaultGraphicsRHI_DX11"), config_path);
        else
            GConfig->SetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), TEXT("DefaultGraphicsRHI_DX12"), config_path);

    GConfig->Flush(false, config_path);  // Save to config
    UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("quit") );  // Exit from game    
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Button_Slider_Value_Changed(const float changed_value)
{
	Set_Tab_Buttons_Settings(changed_value);  // Change setting
	Set_Slider_Text_Block(changed_value);  // Show in UI at which value change
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Settings_Apply()
{
	AsModule_Menu_Config::User_Settings->ApplySettings(false);
	AsModule_Menu_Config::User_Settings->ApplyResolutionSettings(false);  // !!! Maybe move to case when changed?
	AsModule_Menu_Config::User_Settings->SaveConfig();  // Saved to config?
}
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Option_Tab
void UAModule_Menu_Option_Tab::Create_Tab(EModule_Menu_Option_Button_Tabs tab_button, TSubclassOf<UUserWidget> &tab_button_template)
{

	int tab_button_index = 0, tab_size = 0;
	UAModule_Menu_Tab_Button *tab_button_widget = 0;

	Button_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Menu_Option((EModule_Menu_Option_Button_Tabs)tab_button) );  // Button Name

	switch (tab_button)
	{
	case EModule_Menu_Option_Button_Tabs::Graphics:
		tab_size = static_cast<int>(EOption_Type::EPT_Graphic_Last);  // Graphics Tab size | Last valu declared enum
		break;
	case EModule_Menu_Option_Button_Tabs::Gameplay:
		tab_button_index = (int)EOption_Type::EPT_Window_Mode;
		tab_size = (int)EOption_Type::EPT_Last;
		break;
	case EModule_Menu_Option_Button_Tabs::Keyboard:
		break;
	case EModule_Menu_Option_Button_Tabs::Mouse:
		break;
	case EModule_Menu_Option_Button_Tabs::Audio:
		break;
	case EModule_Menu_Option_Button_Tabs::Count:
		break;
	default:
		break;
	}

	for (tab_button_index; tab_button_index < tab_size; tab_button_index++)
	{// Create buttons setting

		tab_button_widget = CreateWidget<UAModule_Menu_Tab_Button>(this, tab_button_template);
		tab_button_widget->Button_Tab_Type = (EOption_Type)tab_button_index;
		tab_button_widget->Button_Setting_Setup();
		Vertical_Box_Tab_Buttons->AddChild(tab_button_widget);
	}
}
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Option
void UAModule_Menu_Option::Create_Menu_Option(TArray<TSubclassOf<UUserWidget> > *widget_type)
{
	UAModule_Menu_Option_Button_Switcher *button_tab_switcher = 0;  // this widget swithes tab
	UAModule_Menu_Option_Tab *tab_widget = 0;  // tab with widgets buttons

	for (int button_index = 0; button_index < (int)EModule_Menu_Option_Button_Tabs::Count; button_index++)
	{// Create buttons and tabs || Init all and 

		button_tab_switcher = CreateWidget<UAModule_Menu_Option_Button_Switcher>(this, (*widget_type)[(int)EModule_Menu_Widget_Type::WT_Option_Button]);
		button_tab_switcher->Create_Button(button_index, Widget_Switcher_Tab);
		Horizontal_Box_Buttons->AddChild(button_tab_switcher);  // Tab Switcher Button

		tab_widget = CreateWidget<UAModule_Menu_Option_Tab>(this, (*widget_type)[(int)EModule_Menu_Widget_Type::WT_Option_Tab]);
		tab_widget->Create_Tab(static_cast<EModule_Menu_Option_Button_Tabs>(button_index), (*widget_type)[(int)EModule_Menu_Widget_Type::WT_Option_Tab_Button]);
		Widget_Switcher_Tab->AddChild(tab_widget);  // Tab Widget
	}
	
	// Redraw Button | Set Switcher | prev button save
	UAModule_Menu_Option_Button_Switcher::Button_Previous = button_tab_switcher;
	UAModule_Menu_Option_Button_Switcher::Button_Previous->Button_Hitbox->SetBackgroundColor(AsModule_Menu_Config::Button_Active);
	Widget_Switcher_Tab->SetActiveWidgetIndex( (int)UAModule_Menu_Option_Button_Switcher::Button_Previous->Button_Switcher_State_Index);
}
//-----------------------------------------------------------------------------------------------------------





// UAModule_Menu_Main_Button
void UAModule_Menu_Main_Button::NativeOnAddedToFocusPath(const FFocusEvent &in_focus_event)
{
	Super::OnAddedToFocusPath(in_focus_event);
	Button_Hovered();
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Main_Button::NativeOnRemovedFromFocusPath(const FFocusEvent &in_focus_event)
{
	Super::OnRemovedFromFocusPath(in_focus_event);
	Button_Unhovered();
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Main_Button::Create_Button(const EModule_Menu_Main_Button_State menu_button_state)
{
	Module_Menu_Button_State = menu_button_state;  // Setup unique index
	Button_Text_Block->SetText(AsModule_Menu_Config::Get_Localization_Text_Menu_Main(Module_Menu_Button_State) );  // Setup button name

	// Bind buttons events 

	Button_Hitbox->OnPressed.AddDynamic(this, &UAModule_Menu_Main_Button::Button_Pressed);
	Button_Hitbox->OnHovered.AddDynamic(this, &UAModule_Menu_Main_Button::Button_Hovered);
	Button_Hitbox->OnUnhovered.AddDynamic(this, &UAModule_Menu_Main_Button::Button_Unhovered);

	PlayAnimation(Button_Animation_Hovered, GetAnimationCurrentTime(Button_Animation_Hovered), 1, EUMGSequencePlayMode::Reverse, 1.0f);  // Play and setup anim to end
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Main_Button::Button_Pressed()
{
	UAModule_Menu_Option *module_menu_option;

	switch (Module_Menu_Button_State)
	{
	case EModule_Menu_Main_Button_State::New_Game:
		UGameplayStatics::OpenLevel(GetWorld(), Level_To_Open);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly() );
		Parent_Ptr->RemoveFromParent();
		break;

	case EModule_Menu_Main_Button_State::Continue:

		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) != Level_To_Open)
			UGameplayStatics::OpenLevel(GetWorld(), Level_To_Open);
		else
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly() );
		Parent_Ptr->RemoveFromParent();
		break;

	case EModule_Menu_Main_Button_State::Settings:
		module_menu_option = CreateWidget<UAModule_Menu_Option>(this, (*Widget_Type)[(int)EModule_Menu_Widget_Type::WT_Option]);
		module_menu_option->Create_Menu_Option(Widget_Type);
		module_menu_option->AddToViewport();
		break;

	case EModule_Menu_Main_Button_State::Arsenals:
		AsModule_Menu_Config::Throw();  // !!! Have No Idea || Underdeveloped
		break;

	case EModule_Menu_Main_Button_State::Achivments:
		AsModule_Menu_Config::Throw();  // !!! Have No Idea || Underdeveloped
		break;

	case EModule_Menu_Main_Button_State::Exit:
		UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Main_Button::Button_Hovered()
{
	if (Button_Animation_Hovered)
		PlayAnimation(Button_Animation_Hovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Main_Button::Button_Unhovered()
{
	if (Button_Animation_Hovered)
		PlayAnimation(Button_Animation_Hovered, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);
}
//-----------------------------------------------------------------------------------------------------------


#include "Engine/LevelStreaming.h" // �������� ���� include

// UAModule_Menu_Main
void UAModule_Menu_Main::Create_Menu_Main(const bool is_continue_button)
{
	APlayerController *player_controller;
	FInputModeUIOnly input_mode_ui_only;
	UAModule_Menu_Main_Button *menu_button_array[(int)EModule_Menu_Main_Button_State::Count];  // All Buttons ptrs || can move to func

	// Get and Apply prev settings in config file
	AsModule_Menu_Config::User_Settings = GEngine->GetGameUserSettings();
	AsModule_Menu_Config::User_Settings->LoadSettings();
	AsModule_Menu_Config::User_Settings->ApplySettings(false);

	for (int i = 0; i < (int)EModule_Menu_Main_Button_State::Count; i++)
	{// Create Menu Main Buttons based on declared buttons state

		menu_button_array[i] = CreateWidget<UAModule_Menu_Main_Button>(this, Module_Widgets[(int)EModule_Menu_Widget_Type::WT_Main_Button]);  // Create widgets based Menu Main Button Template
		menu_button_array[i]->Create_Button( (EModule_Menu_Main_Button_State)i);  // Set unique button state described in class
		Vertical_Box_Menu_Buttons->AddChild(menu_button_array[i]);  // Add widget as child to horizontal box
	}
	
	// 1.0. Add features to unique buttons || New Game Button - Functionality
	menu_button_array[is_continue_button]->Parent_Ptr = this;  // Need to destroy all widgets
	menu_button_array[is_continue_button]->Level_To_Open = New_Game_Level_Open_Name;  // Name to open level while new game pressed button
	menu_button_array[!is_continue_button]->SetIsEnabled(false);  // for New Game

	// 1.1. Option Button, Set templates needed to create all buttons tabs other widgets
	menu_button_array[(int)EModule_Menu_Main_Button_State::Settings]->Parent_Ptr = this;
	menu_button_array[(int)EModule_Menu_Main_Button_State::Settings]->Widget_Type = &Module_Widgets;

	// 2.0. Get and Apply input mode
	input_mode_ui_only.SetWidgetToFocus(menu_button_array[is_continue_button]->TakeWidget() );
	player_controller = GetWorld()->GetFirstPlayerController();
	player_controller->SetShowMouseCursor(true);
	player_controller->SetInputMode(input_mode_ui_only);
	AddToViewport();

}
//----------------------------------------------------------------------------------------------------------- 432(os)  - 452 Lines
