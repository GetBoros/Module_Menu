#pragma once

#include "Module_Menu_Main.h"

#include "GameFramework/GameModeBase.h"
#include "Module_Menu_Game_Mode.generated.h"

// AModule_Menu_Game_Mode
class UGameUserSettings;
//-----------------------------------------------------------------------------------------------------------
UCLASS() class MODULE_MENU_API AAModule_Menu_Game_Mode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAModule_Menu_Game_Mode();

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Can called in BeginPlay cpp | Create Main Menu and other menus options.") ) void Create_Menu_Main();

	UPROPERTY(EditAnywhere, Category = "Init", meta = (ToolTip = "Used to open new level while pressed on New Game M_Button") ) FName New_Game_Level_Open_Name;
	UPROPERTY(EditAnywhere, Category = "Init", meta = (ToolTip = "M_Main | M_Button | M_Option | MO_Button | Tab | T_Button") ) TArray<TSubclassOf<UUserWidget>> Module_Widgets;
};
//-----------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------
#pragma region HOTKEYS
/*
- Quick Search:
	- CTRL + T || + Q ||
- Go To Line:
	- CTRL + G
- Quick if pragma
	- CTRL + K,S  // + 1

*/
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
#pragma region TASKS Menu Main
/*
	- How we can do code better?:
V		- Apply resolution only when released button | Window Mode too | Directx | Show Frame
V		- Toogle Directx show current DX12|11
V		- 70 fps on dxt 11
V		- Frame rate slider text don`t update in shipping show
V	- Make User_Config statis as AsModule_Menu
V	- Try to make as more as can const func or don`t need?

//-----------------------------------------------------------------------------------------------------------
// Current
//-----------------------------------------------------------------------------------------------------------
V	- Quality Presset:
V		- Change other settings like shadow, texture, foliage just update visual in UI
V			- When Change presset need refresh all button | menu quality?
V			- Get All Tab button and call again Get Tab Button Settings?

V	- Menu Main
V		- Can hide background Menu

V	- Localization:
V		- Set Full localization 2 language
V		- Optimaze, Refactoring

V	- New Game Open Level
		- Create Level with simple map without lumen nanite

X	- How to open setting menu in game?
X		- Need think about!

X		- Changed language don`t save, from eng to ru, when restart game again eng
			- Add to .ini localization, and can choose load ru en or elsewhere
X			- When create save / load we load setting with language and just apply language

*/
//-----------------------------------------------------------------------------------------------------------
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
#pragma region TASKS NEED FIX
/*
V	- While toogle show fps it`s not update current state toogled or not
X	- If graphic settings isn`t standart have problem
*/
#pragma endregion
//-----------------------------------------------------------------------------------------------------------
