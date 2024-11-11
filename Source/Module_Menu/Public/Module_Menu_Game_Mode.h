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
		- 
*/