#pragma once
#include <Internationalization/Text.h>

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
	EPT_Toogle_Directx,
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
	static const FText Get_Menu_Main_Text(const EModule_Menu_Main_Button_State menu_main_button_index);  // Localization Template

	static constexpr int Button_Setting_Count = 5;
	static constexpr FLinearColor Button_Active = FLinearColor(0.017642f, 0.026241f, 0.056128f);
	static constexpr FLinearColor Button_Inactive = FLinearColor(0.066626f, 0.341915f, 0.887923f);

	static const FName Button_Name_Defaults[Button_Setting_Count];
	static const FIntPoint Screen_Resolution_Array[Button_Setting_Count];

	static constexpr const wchar_t *Button_Tab_Names[static_cast<int>(EOption_Type::EPT_Last)] = { 
		L"Quality Presset : ", L"Shadows : ", L"Foliage : ", L"Texture : ", L"Shading : ", L"Reflection : ", L"Anti Aliasing : ",
		L"Visual Effects : ", L"View Distances : ", L"Post Processing : ", L"Global Illumination Quality : ", L"",
		L"Window Mode : ", L"Frame Rate : ", L"Screen Resolution : ", L"Screen Percentage : ", L"Toogle Directx : ", L"Show Frame Per Sec" };
	
	static constexpr const wchar_t *Menu_Main_Buttons_Text[static_cast<int>(EModule_Menu_Main_Button_State::Count)] = { L"New Game", L"Continues", L"Options", L"Achievements", L"Arsenal", L"Exit Game" };
	static constexpr const wchar_t *Menu_Option_Buttons_Name[static_cast<int>(EModule_Menu_Option_Button_Tabs::Count)] = { L"Graphics", L"Gameplay", L"Keyboard", L"Audio", L"Mouse" };
	static constexpr const wchar_t *Slider_State[Button_Setting_Count] = { L"Lowest", L"Middle", L"Hight", L"Epic", L"Cinematic" };
	static constexpr const wchar_t *Slider_State_Resoultion[Button_Setting_Count] = { L"960 x 540", L"1280 x 720", L"1920 x 1080", L"2560 x 1440", L"3840 x 2160" };
	static constexpr const wchar_t *Slider_Text_Default[Button_Setting_Count] = { L"Unhandled", L"Custom", L"Toogle", L"Toogled", L"3840 x 2160" };
	static constexpr const wchar_t *Slider_State_Window[3] = { L"FullScreen", L"WndFullScreen", L"Windowed" };  // 0 FullScreen | 1 Windowed Full | 2 Windowed
	static void Throw();
};
//------------------------------------------------------------------------------------------------------------
