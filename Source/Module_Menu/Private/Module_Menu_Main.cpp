#include "Module_Menu_Main.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/GameUserSettings.h"

#include "Components/Slider.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"


// UAModule_Menu_Option_Button
UAModule_Menu_Option_Button *UAModule_Menu_Option_Button::Button_Previous = 0;
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Option_Button::Init(const int button_index, UWidgetSwitcher *widget_switcher)
{
	Button_Text_Block->SetText(FText::FromString(AsModule_Menu_Config::Menu_Option_Buttons_Name[(int)button_index]) );  // Button Name
	WidgetSwitcher_Tab = widget_switcher;
	Option_Button_Name = (EModule_Menu_Option_Button_Name)button_index;
	Button_Hitbox->OnPressed.AddDynamic(this, &UAModule_Menu_Option_Button::Button_Pressed);  // What to do if pressed on button
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Option_Button::Button_Pressed()
{
	Button_Previous->Button_Hitbox->SetBackgroundColor(AsModule_Menu_Config::Button_Inactive);  // Redraw prev button to inactive
	Button_Previous = this;  // not this button is previous
	Button_Hitbox->SetBackgroundColor(AsModule_Menu_Config::Button_Active);  // Draw this button as active
	WidgetSwitcher_Tab->SetActiveWidgetIndex( (int)Option_Button_Name);  // Switch Tab
}
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Tab_Button
void UAModule_Menu_Tab_Button::Init()
{
	Slider_Text_Value = AsModule_Menu_Config::Slider_Text_Default[(int)ESlider_Text_State::Unhandled];  // !!!

	User_Settings = GEngine->GetGameUserSettings();
	Button_Slider->SetStepSize(1.0f);
	Button_Slider->SetMaxValue(4.0f);  // Max setting when 4 is Cinematic and 0 is lowest quality
	Button_Slider->MouseUsesStep = true;  // Slider Step
	Button_Text_Block->SetText(FText::FromString(AsModule_Menu_Config::Button_Tab_Names[(int)Button_Tab_Type]) );  // Button Name
	Get_Button_Tab_State();

	Button_Slider->OnValueChanged.AddDynamic(this, &UAModule_Menu_Tab_Button::Set_Button_Tab_State);  // What to do if pressed on button
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Button_State_Upate()
{

}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Get_Button_Tab_State()
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
	case EOption_Type::EPT_Window_Mode:
		Button_Slider->SetMaxValue(3.0f);
		button_index = (EWindowMode::Type)User_Settings->GetDefaultWindowMode();
		Slider_Text_Value = AsModule_Menu_Config::Slider_State_Window[(int)button_index];
		break;
	case EOption_Type::EPT_Frame_Rate:
		Button_Slider->SetMinValue(24.0f);
		Button_Slider->SetMaxValue(144.0f);
		button_index = (int)User_Settings->GetFrameRateLimit();
		Slider_Text_Value = FString::FromInt(button_index);
		break;
	case EOption_Type::EPT_Screen_Resolution:
		int_point = User_Settings->GetScreenResolution();
		for (i = 0; i < AsModule_Menu_Config::Button_Setting_Count; i++)  // Find current screen resolution | need to redraw current setting
			if (AsModule_Menu_Config::Screen_Resolution_Array[i] == int_point)
				Slider_Text_Value = AsModule_Menu_Config::Slider_State_Resoultion[(int)(button_index = i)];
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
		Slider_Text_Value = AsModule_Menu_Config::Slider_Text_Default[(int)ESlider_Text_State::Toogle]; // L"Toogle";
		break;
	}
	
	// Make Func
	if (EOption_Type::EPT_Graphic_Last > Button_Tab_Type)  // Handle quality settings other is unique
		if (button_index == -1)  // If presset is custom show it
			Slider_Text_Block->SetText(FText::FromString(AsModule_Menu_Config::Slider_Text_Default[(int)ESlider_Text_State::Custom_Settings]) );  // !!! Only when Pressed is not standart
		else
			Slider_Text_Value = AsModule_Menu_Config::Slider_State[(int)button_index];  // Set Quality state

	Slider_Text_Block->SetText(FText::FromString(Slider_Text_Value) );  // Set Unique state
	Button_Slider->SetValue(button_index);  // Apply slider settings
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Tab_Button::Set_Button_Tab_State(float changed_value)
{
	int Widget_Index = (int)Button_Slider->GetValue();
	
	switch (Button_Tab_Type)
	{
	case EOption_Type::EPT_Quality_Presset:
		User_Settings->SetOverallScalabilityLevel(Widget_Index);
		break;
	case EOption_Type::EPT_Quality_Shadows:
		User_Settings->SetShadowQuality(Widget_Index);
		break;
	case EOption_Type::EPT_Quality_Foliage:
		User_Settings->SetFoliageQuality(Widget_Index);
		break;
	case EOption_Type::EPT_Quality_Texture:
		User_Settings->SetTextureQuality(Widget_Index);
		break;
	case EOption_Type::EPT_Quality_Shading:
		User_Settings->SetShadingQuality(Widget_Index);
		break;
	case EOption_Type::EPT_Quality_Reflection:
		User_Settings->SetReflectionQuality(Widget_Index);
		break;
	case EOption_Type::EPT_Quality_Anti_Aliasing:
		User_Settings->SetAntiAliasingQuality(Widget_Index);
		break;
	case EOption_Type::EPT_Quality_Visual_Effects:
		User_Settings->SetVisualEffectQuality(Widget_Index);
		break;
	case EOption_Type::EPT_Quality_View_Distances:
		User_Settings->SetViewDistanceQuality(Widget_Index);
		break;
	case EOption_Type::EPT_Quality_Post_Processing:
		User_Settings->SetPostProcessingQuality(Widget_Index);
		break;
	case EOption_Type::EPT_Quality_Global_Illumination_Quality:
		User_Settings->SetGlobalIlluminationQuality(Widget_Index);
		break;
		case EOption_Type::EPT_Window_Mode:
		User_Settings->SetFullscreenMode(EWindowMode::ConvertIntToWindowMode(Widget_Index) );
		Slider_Text_Value = AsModule_Menu_Config::Slider_State_Window[(int)Widget_Index];
		User_Settings->ApplyResolutionSettings(false);
		break;
	case EOption_Type::EPT_Frame_Rate:
		User_Settings->SetFrameRateLimit(Widget_Index);
		break;
	case EOption_Type::EPT_Screen_Resolution:
		User_Settings->SetScreenResolution(AsModule_Menu_Config::Screen_Resolution_Array[(int)Widget_Index]);
		Slider_Text_Value = AsModule_Menu_Config::Slider_State_Resoultion[(int)Widget_Index];
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
	
	if (EOption_Type::EPT_Graphic_Last > Button_Tab_Type)  // Handle quality settings other is unique
		if (Widget_Index == -1)  // If presset is custom show it
			Slider_Text_Value = AsModule_Menu_Config::Slider_Text_Default[(int)ESlider_Text_State::Custom_Settings];
		else
			Slider_Text_Value = AsModule_Menu_Config::Slider_State[(int)Widget_Index];
	Slider_Text_Block->SetText(FText::FromString(Slider_Text_Value) );  // Slider Effects
	User_Settings->ApplySettings(false);
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




// UAModule_Menu_Option_Tab
void UAModule_Menu_Option_Tab::Init(const int button_index, TSubclassOf<UUserWidget> tab_button_template)
{// !!! Refactoring

	int index = 0;
	int tab_size = 0;
	UAModule_Menu_Tab_Button *tab_button_widget;

	Button_Text_Block->SetText(FText::FromString(AsModule_Menu_Config::Menu_Option_Buttons_Name[(int)button_index]) );  // Button Name

	switch ( (EModule_Menu_Option_Button_Name)button_index)
	{
	case EModule_Menu_Option_Button_Name::Button_Graphics:
		index = 0;
		tab_size = (int)EOption_Type::EPT_Graphic_Last;
		break;

	case EModule_Menu_Option_Button_Name::Button_Gameplay:
		index = (int)EOption_Type::EPT_Window_Mode;
		tab_size = (int)EOption_Type::EPT_Last;
		break;

	case EModule_Menu_Option_Button_Name::Button_Keyboard:
		break;
	case EModule_Menu_Option_Button_Name::Button_Mouse:
		break;
	case EModule_Menu_Option_Button_Name::Button_Audio:
		break;
	case EModule_Menu_Option_Button_Name::Buttons_Count:
		break;

	default:
		return;
		break;
	}

	for (index; index < tab_size; index++)
	{
		tab_button_widget = CreateWidget<UAModule_Menu_Tab_Button>(this, tab_button_template);
		VerticalBox_Root->AddChild(tab_button_widget);
		tab_button_widget->Button_Tab_Type = (EOption_Type)index;
		tab_button_widget->Init();
	}
}
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Option
void UAModule_Menu_Option::Init_Menu_Option(TSubclassOf<UUserWidget> button_template, TSubclassOf<UUserWidget> tab_template, TSubclassOf<UUserWidget> tab_button_template)
{
	int i = 0;
	UAModule_Menu_Option_Tab *tab_button = 0;  // tab with widgets buttons
	UAModule_Menu_Option_Button *button_tab = 0;  // this widget swithes tab

	for (i = 0; i < (int)EModule_Menu_Option_Button_Name::Buttons_Count; i++)
	{// Create buttons and tabs || Inits all and 

		button_tab = CreateWidget<UAModule_Menu_Option_Button>(this, button_template);
		tab_button = CreateWidget<UAModule_Menu_Option_Tab>(this, tab_template);

		button_tab->Init(i, WidgetSwitcher_Tab);
		tab_button->Init(i, tab_button_template);  // Create buttons in tabs

		HorizontalBox_Buttons->AddChild(button_tab);
		WidgetSwitcher_Tab->AddChild(tab_button);
	}
	
	// !!! Idea || If have save load system can load prev opened tag set it here and draw as active
	UAModule_Menu_Option_Button::Button_Previous = button_tab;
	UAModule_Menu_Option_Button::Button_Previous->Button_Hitbox->SetBackgroundColor(AsModule_Menu_Config::Button_Active);
	WidgetSwitcher_Tab->SetActiveWidgetIndex( (int)UAModule_Menu_Option_Button::Button_Previous->Option_Button_Name);
}
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Main_Button
void UAModule_Menu_Main_Button::Init()
{
	const FString button_name(AsModule_Menu_Config::Menu_Main_Buttons_Text[(int)Module_Menu_Button_State]);
	
	if (button_name.IsEmpty() && Button_Animation_Hovered != 0)  // !!! Don`t need
		AsModule_Menu_Config::Throw();
	if (!Button_Hitbox != 0)
		return;
	Button_Text_Block->SetText(FText::FromString(button_name) );  // Button Name
	Button_Hitbox->OnPressed.AddDynamic(this, &UAModule_Menu_Main_Button::Button_Pressed);  // What to do if pressed on button
	Button_Hitbox->OnHovered.AddDynamic(this, &UAModule_Menu_Main_Button::Button_Hovered);
	Button_Hitbox->OnUnhovered.AddDynamic(this, &UAModule_Menu_Main_Button::Button_Unhovered);
	
	PlayAnimation(Button_Animation_Hovered, GetAnimationCurrentTime(Button_Animation_Hovered), 1, EUMGSequencePlayMode::Reverse, 1.0f);  // Anim to end
}
//-----------------------------------------------------------------------------------------------------------
void UAModule_Menu_Main_Button::Button_Pressed()
{
	switch (Module_Menu_Button_State)
	{
	case EModule_Menu_Button_State::Button_Start_New_Game:
		Parent_Ptr->RemoveFromParent();
		UGameplayStatics::OpenLevel(this, Level_To_Open, true);  // !!! Change to dinamyc FName || Open New Level || Those level has his own Game Mode set it if u need it
		break;

	case EModule_Menu_Button_State::Button_Continues_Game:
		//UGameplayStatics::OpenLevel(this, Level_To_Open, true);  // !!! Change to dinamyc FName || Open New Level || Those level has his own Game Mode set it if u need it
		break;

	case EModule_Menu_Button_State::Button_Open_Options:
	{
		UAModule_Menu_Option *module_menu_option;

		module_menu_option = CreateWidget<UAModule_Menu_Option>(this, Module_Menu_Option);
		//module_menu_option = CreateWidget<UAModule_Menu_Option>(GetWorld()->GetFirstPlayerController(), Module_Menu_Option);
		module_menu_option->AddToViewport();
		module_menu_option->Init_Menu_Option(Module_Menu_Option_Button, Module_Menu_Option_Tab, Module_Menu_Tab_Button);
	}
		break;

	case EModule_Menu_Button_State::Button_Open_Achievements:
		AsModule_Menu_Config::Throw();  // !!! Have No Idea || Underdeveloped
		break;

	case EModule_Menu_Button_State::Button_Open_Arsenal:
		AsModule_Menu_Config::Throw();  // !!! Have No Idea || Underdeveloped
		break;

	case EModule_Menu_Button_State::Button_Exit_Game:
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
void UAModule_Menu_Main::Buttons_Menu_Init(const FName &level, const TSubclassOf<UUserWidget> &m_button, const TSubclassOf<UUserWidget> &m_option,
	const TSubclassOf<UUserWidget> &m_o_button, const TSubclassOf<UUserWidget> &m_o_tab, const TSubclassOf<UUserWidget> &m_o_tab_button)
{
	for (int i = 0; i < (int)EModule_Menu_Button_State::Buttons_Count; i++)
	{// Create Menu Main Buttons

		Button_Menu_Main[i] = CreateWidget<UAModule_Menu_Main_Button>(this, m_button);  // Create widgets baset on Button_Menu_Template
		Button_Menu_Main[i]->Module_Menu_Button_State = (EModule_Menu_Button_State)i;  // Set Button feature
		Button_Menu_Main[i]->Init();  // Need Apply Button Settings

		VerticalBox_Root->AddChild(Button_Menu_Main[i]);  // Add widget as child to horrizontal box
	}

	// 1.0. Add features to unique buttons
	Button_Menu_Main[(int)EModule_Menu_Button_State::Button_Start_New_Game]->Parent_Ptr = this;
	Button_Menu_Main[(int)EModule_Menu_Button_State::Button_Start_New_Game]->Level_To_Open = level;

	Button_Menu_Main[(int)EModule_Menu_Button_State::Button_Open_Options]->Parent_Ptr = this;
	Button_Menu_Main[(int)EModule_Menu_Button_State::Button_Open_Options]->Module_Menu_Option = m_option;
	Button_Menu_Main[(int)EModule_Menu_Button_State::Button_Open_Options]->Module_Menu_Option_Button = m_o_button;
	Button_Menu_Main[(int)EModule_Menu_Button_State::Button_Open_Options]->Module_Menu_Option_Tab = m_o_tab;
	Button_Menu_Main[(int)EModule_Menu_Button_State::Button_Open_Options]->Module_Menu_Tab_Button = m_o_tab_button;
}
//-----------------------------------------------------------------------------------------------------------
