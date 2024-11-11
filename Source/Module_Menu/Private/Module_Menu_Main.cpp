#include "Module_Menu_Main.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

#include "Components/Slider.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"  // WW
#include "Components/VerticalBox.h"  // WW

// UAModule_Menu_Option_Button_Switcher
UAModule_Menu_Option_Button_Switcher *UAModule_Menu_Option_Button_Switcher::Button_Previous = 0;
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Option_Button_Switcher::Create_Button(const int button_index, UWidgetSwitcher *widget_switcher)
{
	WidgetSwitcher_Tab = widget_switcher;
	Button_Switcher_State_Index = (EModule_Menu_Option_Button_Tabs)button_index;

	Button_Text_Block->SetText(FText::FromString(AsModule_Menu_Config::Menu_Option_Buttons_Name[(int)button_index]) );  // Set button name
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
	User_Settings = GEngine->GetGameUserSettings();
	Slider_Text_Value = AsModule_Menu_Config::Slider_Text_Default[(int)ESlider_Text_State::Unhandled];
	
	Button_Text_Block->SetText(FText::FromString(AsModule_Menu_Config::Button_Tab_Names[(int)Button_Tab_Type]) );  // Button Name
	Button_Slider->SetStepSize(1.0f);
	Button_Slider->SetMaxValue(4.0f);  // Max setting when 4 is Cinematic and 0 is lowest quality
	Button_Slider->MouseUsesStep = true;  // floor or clamp effect | offset to stepsize

	Get_Tab_Buttons_Settings();

	Button_Slider->OnValueChanged.AddDynamic(this, &UAModule_Menu_Tab_Button::Button_Slider_Value_Changed);  // What to do if pressed on button
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Get_Tab_Buttons_Settings()
{
	int i = 0;
	float button_index = 0.0f;
	FIntPoint int_point {};

	switch (Button_Tab_Type)
	{// For current button type have unique button setting || Get Setting to an apply it || And Limiting Sliders for unique settings

	case EOption_Type::EPT_Quality_Presset:
		button_index = User_Settings->GetOverallScalabilityLevel();
		break;
	case EOption_Type::EPT_Quality_Shadows:
		button_index = User_Settings->GetShadowQuality();
		break;
	case EOption_Type::EPT_Quality_Foliage:
		button_index = User_Settings->GetFoliageQuality();
		break;
	case EOption_Type::EPT_Quality_Texture:
		button_index = User_Settings->GetTextureQuality();
		break;
	case EOption_Type::EPT_Quality_Shading:
		button_index = User_Settings->GetShadingQuality();
		break;
	case EOption_Type::EPT_Quality_Reflection:
		button_index = User_Settings->GetReflectionQuality();
		break;
	case EOption_Type::EPT_Quality_Anti_Aliasing:
		button_index = User_Settings->GetAntiAliasingQuality();
		break;
	case EOption_Type::EPT_Quality_Visual_Effects:
		button_index = User_Settings->GetVisualEffectQuality();
		break;
	case EOption_Type::EPT_Quality_View_Distances:
		button_index = User_Settings->GetViewDistanceQuality();
		break;
	case EOption_Type::EPT_Quality_Post_Processing:
		button_index = User_Settings->GetPostProcessingQuality();
		break;
	case EOption_Type::EPT_Quality_Global_Illumination_Quality:
		button_index = User_Settings->GetGlobalIlluminationQuality();
		break;
	case EOption_Type::EPT_Window_Mode:  // !!! Bad To apply imediatly
		Button_Slider->SetMaxValue(2.0f);
		button_index = User_Settings->GetFullscreenMode();
		User_Settings->SetFullscreenMode((EWindowMode::Type)button_index);
		User_Settings->ApplySettings(false);
		Slider_Text_Value = AsModule_Menu_Config::Slider_State_Window[(int)button_index];
		break;
	case EOption_Type::EPT_Frame_Rate:
		Button_Slider->SetMinValue(24.0f);
		Button_Slider->SetMaxValue(144.0f);
		button_index = (int)User_Settings->GetFrameRateLimit();
		Slider_Text_Value = FString::FromInt(button_index);
		break;
	case EOption_Type::EPT_Screen_Resolution:  // Fix those
		int_point = User_Settings->GetScreenResolution();
		for (i = 0; i < AsModule_Menu_Config::Button_Setting_Count; i++)  // Find current screen resolution | need to redraw current setting
			if (AsModule_Menu_Config::Screen_Resolution_Array[i] == int_point)
				button_index = i;
		Slider_Text_Value = AsModule_Menu_Config::Slider_State_Resoultion[(int)button_index];
		break;
	case EOption_Type::EPT_Screen_Percentage:
		Button_Slider->SetStepSize(0.1f);
		Button_Slider->SetMinValue(0.3f);
		Button_Slider->SetMaxValue(1.0f);
		button_index = User_Settings->GetResolutionScaleNormalized();
		Slider_Text_Value = FString::FromInt( (int)(button_index * 100.0f) );
		break;
	case EOption_Type::EPT_Toogle_Directx:
	case EOption_Type::EPT_Show_Frame_Per_Sec:
		Button_Slider->SetMinValue(0.0f);
		Button_Slider->SetMaxValue(1.0f);
		Slider_Text_Value = AsModule_Menu_Config::Slider_Text_Default[(int)ESlider_Text_State::Toogle];
		break;
	}
	
	Slider_Text_Block_Update(button_index);
	Button_Slider->SetValue(button_index);  // Apply slider settings
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Set_Tab_Buttons_Settings(const float changed_value)
{
	switch (Button_Tab_Type)
	{
	case EOption_Type::EPT_Quality_Presset:
		User_Settings->SetOverallScalabilityLevel(changed_value);
		break;
	case EOption_Type::EPT_Quality_Shadows:
		User_Settings->SetShadowQuality(changed_value);
		break;
	case EOption_Type::EPT_Quality_Foliage:
		User_Settings->SetFoliageQuality(changed_value);
		break;
	case EOption_Type::EPT_Quality_Texture:
		User_Settings->SetTextureQuality(changed_value);
		break;
	case EOption_Type::EPT_Quality_Shading:
		User_Settings->SetShadingQuality(changed_value);
		break;
	case EOption_Type::EPT_Quality_Reflection:
		User_Settings->SetReflectionQuality(changed_value);
		break;
	case EOption_Type::EPT_Quality_Anti_Aliasing:
		User_Settings->SetAntiAliasingQuality(changed_value);
		break;
	case EOption_Type::EPT_Quality_Visual_Effects:
		User_Settings->SetVisualEffectQuality(changed_value);
		break;
	case EOption_Type::EPT_Quality_View_Distances:
		User_Settings->SetViewDistanceQuality(changed_value);
		break;
	case EOption_Type::EPT_Quality_Post_Processing:
		User_Settings->SetPostProcessingQuality(changed_value);
		break;
	case EOption_Type::EPT_Quality_Global_Illumination_Quality:
		User_Settings->SetGlobalIlluminationQuality(changed_value);
		break;
	case EOption_Type::EPT_Window_Mode:
		User_Settings->SetFullscreenMode(EWindowMode::ConvertIntToWindowMode( (int)changed_value) );
		Slider_Text_Value = AsModule_Menu_Config::Slider_State_Window[(int)changed_value];
		break;
	case EOption_Type::EPT_Frame_Rate:
		User_Settings->SetFrameRateLimit(changed_value);
		break;
	case EOption_Type::EPT_Screen_Resolution:
		User_Settings->SetScreenResolution(AsModule_Menu_Config::Screen_Resolution_Array[(int)changed_value]);
		User_Settings->ApplyResolutionSettings(false);
		Slider_Text_Value = AsModule_Menu_Config::Slider_State_Resoultion[(int)changed_value];
		break;
	case EOption_Type::EPT_Screen_Percentage:
		User_Settings->SetResolutionScaleNormalized(changed_value);
		Slider_Text_Value = FString::FromInt( (int)(changed_value * 100.0f) );
		break;
	case EOption_Type::EPT_Toogle_Directx:
		Toogle_Directx();
		Slider_Text_Value = AsModule_Menu_Config::Slider_Text_Default[(int)ESlider_Text_State::Toogled];
		break;
	case EOption_Type::EPT_Show_Frame_Per_Sec:
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("stat fps") );  // Exit from game
		Slider_Text_Value = AsModule_Menu_Config::Slider_Text_Default[(int)ESlider_Text_State::Toogled];
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Slider_Text_Block_Update(const int button_index)
{
	if (EOption_Type::EPT_Graphic_Last > Button_Tab_Type)  // Handle quality settings other is unique
		if (button_index == -1)  // If presset is custom show it
			Slider_Text_Value = AsModule_Menu_Config::Slider_Text_Default[(int)ESlider_Text_State::Custom_Settings];
		else
			Slider_Text_Value = AsModule_Menu_Config::Slider_State[(int)button_index];

	Slider_Text_Block->SetText(FText::FromString(Slider_Text_Value) );  // Slider Effects
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Toogle_Directx()
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
	Set_Tab_Buttons_Settings(changed_value);
	Slider_Text_Block_Update(changed_value);

	User_Settings->ApplySettings(false);
	User_Settings->SaveConfig();  // Saved to config?
}
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Option_Tab
void UAModule_Menu_Option_Tab::Create_Tab(EModule_Menu_Option_Button_Tabs tab_button, TSubclassOf<UUserWidget> &tab_button_template)
{

	int tab_button_index = 0, tab_size = 0;
	UAModule_Menu_Tab_Button *tab_button_widget = 0;

	Button_Text_Block->SetText(FText::FromString(AsModule_Menu_Config::Menu_Option_Buttons_Name[(int)tab_button]) );  // Button Name

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
void UAModule_Menu_Option::Create_Menu_Option(TArray<TSubclassOf<UUserWidget>> *widget_type)
{
	UAModule_Menu_Option_Button_Switcher *button_tab_switcher = 0;  // this widget swithes tab
	UAModule_Menu_Option_Tab *tab_widget = 0;  // tab with widgets buttons

	for (int button_index = 0; button_index < (int)EModule_Menu_Option_Button_Tabs::Count; button_index++)
	{// Create buttons and tabs || Inits all and 

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
void UAModule_Menu_Main_Button::Create_Button(const EModule_Menu_Main_Button_State menu_button_state)
{
	Module_Menu_Button_State = menu_button_state;  // Setup unique index
	Button_Text_Block->SetText(AsModule_Menu_Config::Get_Menu_Main_Text(Module_Menu_Button_State) );  // Setup button name

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
		Parent_Ptr->RemoveFromParent();
		UGameplayStatics::OpenLevel(this, Level_To_Open, true);
		break;

	case EModule_Menu_Main_Button_State::Continue:
		//Parent_Ptr->RemoveFromParent();
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
		PlayAnimation(Button_Animation_Hovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);  // ¬оспроизводим анимацию вперед
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Main_Button::Button_Unhovered()
{
	if (Button_Animation_Hovered)
		PlayAnimation(Button_Animation_Hovered, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);  // ¬оспроизводим анимацию в обратном пор€дке
}
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Main
void UAModule_Menu_Main::Buttons_Menu_Setup(const FName &level, TArray<TSubclassOf<UUserWidget>> &widget_type)
{
	UAModule_Menu_Main_Button *menu_button_array[(int)EModule_Menu_Main_Button_State::Count];  // All Buttons ptrs || can move to func
	
	for (int i = 0; i < (int)EModule_Menu_Main_Button_State::Count; i++)
	{// Create Menu Main Buttons based on declared buttons state

		menu_button_array[i] = CreateWidget<UAModule_Menu_Main_Button>(this, widget_type[(int)EModule_Menu_Widget_Type::WT_Main_Button]);  // Create widgets based Menu Main Button Template
		menu_button_array[i]->Create_Button( (EModule_Menu_Main_Button_State)i);  // Set unique button state described in class
		Vertical_Box_Menu_Buttons->AddChild(menu_button_array[i]);  // Add widget as child to horrizontal box
	}

	// 1.0. Add features to unique buttons
	menu_button_array[(int)EModule_Menu_Main_Button_State::New_Game]->Parent_Ptr = this;  // Need to destroy all widgets
	menu_button_array[(int)EModule_Menu_Main_Button_State::New_Game]->Level_To_Open = level;  // Name to open level while new game pressed button

	// 1.1. Option Button, Set templates needet to create all buttons tabs other widgets
	menu_button_array[(int)EModule_Menu_Main_Button_State::Settings]->Parent_Ptr = this;
	menu_button_array[(int)EModule_Menu_Main_Button_State::Settings]->Widget_Type = &widget_type;
}
//-----------------------------------------------------------------------------------------------------------
