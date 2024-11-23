#pragma once
#include "GameFramework/GameUserSettings.h"

// ENUMS
enum class EModule_Menu_Main_Button_State : uint8
{
    New_Game,
    Continue,
    Settings,
    Arsenals,
    Achivments,
    Exit,
	Count
};
//------------------------------------------------------------------------------------------------------------
enum class EModule_Menu_Option_Button_Tabs : uint8
{
    Graphics = 0,
    Gameplay,
    Keyboard,
    Mouse,
    Audio,
	Count
};
//------------------------------------------------------------------------------------------------------------
enum class EOption_Type : uint8
{
	// Graphics
	EPT_Quality_Presset,
	EPT_Quality_Shadows,
	EPT_Quality_Foliage,
	EPT_Quality_Texture,
	EPT_Quality_Shading,
	EPT_Quality_Reflection,
	EPT_Quality_Anti_Aliasing,
	EPT_Quality_Visual_Effects,
	EPT_Quality_View_Distances,
	EPT_Quality_Post_Processing,
	EPT_Quality_Global_Illumination_Quality,
	EPT_Graphic_Last,
	// Gameplay
	EPT_Window_Mode,
	EPT_Frame_Rate,
	EPT_Screen_Resolution,
	EPT_Screen_Percentage,
	EPT_DirectX_Switcher,
	EPT_Show_Frame_Per_Sec,
	EPT_Last
};
//----------------------------------------------------------------------------------------------------------- 
enum class ESlider_Text_State : uint8
{
	Unhandled,
	Custom_Settings,
	Toogle,
	Toogled,
	Count
};
//----------------------------------------------------------------------------------------------------------- 
enum class EModule_Menu_Widget_Type : uint8
{
	WT_Main,
	WT_Main_Button,
	WT_Option,
	WT_Option_Button,
	WT_Option_Tab,
	WT_Option_Tab_Button,
	WT_Count
};
//----------------------------------------------------------------------------------------------------------- 




// AsModule_Menu_Config
class MODULE_MENU_API AsModule_Menu_Config
{
public:
	static const FText Get_Localization_Text_Menu_Main(const EModule_Menu_Main_Button_State menu_main_button_index);  // Localized Menu Buttons
	static const FText Get_Localization_Text_Menu_Option(const EModule_Menu_Option_Button_Tabs menu_main_button_index);  // Localized Menu Options Button Tabs

	static const FText Get_Localization_Text_Slider_State_Window(const int slider_window_state);  // Localized Window State
	static const FText Get_Localization_Text_Slider_State_Default(const int button_setting_count);  // Localized State Default
	static const FText Get_Localization_Text_Slider_State_Custom(const int button_setting_count);  // Localized State Resolution

	static const FText Get_Localization_Text_Tab_Button_Name(const EOption_Type button_type);  // Localized State Resolution

	static UGameUserSettings *User_Settings;

	static constexpr int Button_Setting_Count = 5;
	static constexpr const wchar_t *Slider_State_Resoultion[Button_Setting_Count] = { L"960 x 540", L"1280 x 720", L"1920 x 1080", L"2560 x 1440", L"3840 x 2160" };
	static constexpr FLinearColor Button_Active = FLinearColor(0.017642f, 0.026241f, 0.056128f);
	static constexpr FLinearColor Button_Inactive = FLinearColor(0.066626f, 0.341915f, 0.887923f);

	static const FName Button_Name_Defaults[Button_Setting_Count];
	static const FIntPoint Screen_Resolution_Array[Button_Setting_Count];
	
	static const void Throw();
};
//------------------------------------------------------------------------------------------------------------
