#pragma once

#include <functional>
#include "CoreMinimal.h"

// EButtonState
/*
    - Only Menu Main not Options
    - Set in menu main buttons
    - Has unique features realised in Button
	CollectGarbage(RF_NoFlags);  // !!! TEMP Test Call Garbage collector || Free memory

*/
UENUM(BlueprintType) enum class EModule_Menu_Button_State : uint8
{
    Button_Start_New_Game,
    Button_Continues_Game,
    Button_Open_Options,
    Button_Open_Achievements,
    Button_Open_Arsenal,
    Button_Exit_Game,
	Buttons_Count
};
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType) enum class EModule_Menu_Option_Button_Name : uint8
{
    Button_Graphics,
    Button_Gameplay,
    Button_Keyboard,
    Button_Mouse,
    Button_Audio,
	Buttons_Count
};
//------------------------------------------------------------------------------------------------------------

// EOption_Type
UENUM(BlueprintType) enum class EOption_Type : uint8
{
	// Graphics
	EPT_Quality_Presset UMETA(DisplayName = "EPT_Quality_Presset"),
	EPT_Quality_Shadows UMETA(DisplayName = "EPT_Quality_Shadows"),
	EPT_Quality_Foliage UMETA(DisplayName = "EPT_Quality_Foliage"),
	EPT_Quality_Texture UMETA(DisplayName = "EPT_Quality_Texture"),
	EPT_Quality_Shading UMETA(DisplayName = "EPT_Quality_Shading"),
	EPT_Quality_Reflection UMETA(DisplayName = "EPT_Quality_Reflection"),
	EPT_Quality_Anti_Aliasing UMETA(DisplayName = "EPT_Quality_Anti_Aliasing"),
	EPT_Quality_Visual_Effects UMETA(DisplayName = "EPT_Quality_Visual_Effects"),
	EPT_Quality_View_Distances UMETA(DisplayName = "EPT_Quality_View_Distances"),
	EPT_Quality_Post_Processing UMETA(DisplayName = "EPT_Quality_Post_Processing"),
	EPT_Quality_Global_Illumination_Quality UMETA(DisplayName = "EPT_Quality_Global_Illumination_Quality"),
	EPT_Graphic_Last,
	// Gameplay
	EPT_Window_Mode UMETA(DisplayName = "EPT_Window_Mode"),
	EPT_Frame_Rate UMETA(DisplayName = "EPT_Frame_Rate"),
	EPT_Screen_Resolution UMETA(DisplayName = "EPT_Screen_Resolution"),
	EPT_Screen_Percentage UMETA(DisplayName = "EPT_Screen_Percentage"),
	EPT_Toogle_Directx UMETA(DisplayName = "EPT_Toogle_Directx"),
	EPT_Show_Frame_Per_Sec UMETA(DisplayName = "EPT_Show_Frame_Per_Sec"),
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



// AsModule_Menu_Config
class MODULE_MENU_API AsModule_Menu_Config
{
public:
	~AsModule_Menu_Config();
	AsModule_Menu_Config();

	static constexpr int Button_Setting_Count = 5;
	static constexpr FLinearColor Button_Active = FLinearColor(0.017642f, 0.026241f, 0.056128f);
	static constexpr FLinearColor Button_Inactive = FLinearColor(0.066626f, 0.341915f, 0.887923f);

	static const FName Button_Name_Defaults[Button_Setting_Count];
	static const FIntPoint Screen_Resolution_Array[Button_Setting_Count];

	static constexpr const wchar_t *Button_Tab_Names[static_cast<int>(EOption_Type::EPT_Last)] = {
		L"Quality Presset : ", L"Shadows : ", L"Foliage : ", L"Texture : ", L"Shading : ", L"Reflection : ", L"Anti Aliasing : ",
		L"Visual Effects : ", L"View Distances : ", L"Post Processing : ", L"Global Illumination Quality : ", L"",
		L"Window Mode : ", L"Frame Rate : ", L"Screen Resolution : ", L"Screen Percentage : ", L"Toogle Directx : ", L"Show Frame Per Sec" };
	
	static constexpr const wchar_t *Menu_Option_Buttons_Name[static_cast<int>(EModule_Menu_Option_Button_Name::Buttons_Count)] = { L"Graphics", L"Gameplay", L"Keyboard", L"Audio", L"Mouse" };
	static constexpr const wchar_t *Menu_Main_Buttons_Text[static_cast<int>(EModule_Menu_Button_State::Buttons_Count)] = { L"New Game", L"Continues", L"Options", L"Achievements", L"Arsenal", L"Exit Game" };
	static constexpr const wchar_t *Slider_State[Button_Setting_Count] = { L"Lowest", L"Middle", L"Hight", L"Epic", L"Cinematic" };
	static constexpr const wchar_t *Slider_State_Resoultion[Button_Setting_Count] = { L"960 x 540", L"1280 x 720", L"1920 x 1080", L"2560 x 1440", L"3840 x 2160" };
	static constexpr const wchar_t *Slider_Text_Default[Button_Setting_Count] = { L"Unhandled", L"Custom", L"Toogle", L"Toogled", L"3840 x 2160" };
	static constexpr const wchar_t *Slider_State_Window[3] = { L"FullScreen", L"WndFullScreen", L"Windowed" };  // 0 FullScreen | 1 Windowed Full | 2 Windowed
	static void Throw();
};
//------------------------------------------------------------------------------------------------------------
