#pragma once

#include "Module_Menu_Main.h"

#include "GameFramework/GameModeBase.h"
#include "Module_Menu_Game_Mode.generated.h"

// AModule_Menu_Game_Mode
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




// TASKS
/*
	- How we can do code better?:
V		- Apply resolution only when released button | Window Mode too | Directx | Show Frame
V		- Toogle Directx show current DX12|11
V		- 70 fps on dxt 11
V		- Frame rate slider text don`t update in shipping show
V	- Make User_Config statis as AsModule_Menu
	- Quality Presset:
		- Change other settings like shadow, texture, foliage just update visual in UI
			- When Change presset need refresh all button | menu quality?
			- Get All Tab button and call again Get Tab Button Settings?

	- Hide Menu Main when press on Option:
		- Show character or mesh to show current quality?
		- If Menu Main Collapse how to set visible
*/

// SOMEDAY
/*
X		- Changed language don`t save, from eng to ru, when restart game again eng
			- Add to .ini localization, and can choose load ru en or elsewhere

*/

// HOTKEYS
/*
	- Quick Search:
		- CTRL + T || + Q || 
	- Go To Line:
		- CTRL + G


*/