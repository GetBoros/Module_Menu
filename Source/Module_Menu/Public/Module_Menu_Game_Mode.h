#pragma once

#include "Module_Menu_Main.h"

#include "GameFramework/GameModeBase.h"
#include "Module_Menu_Game_Mode.generated.h"

// AModule_Menu_Game_Mode
UCLASS() class MODULE_MENU_API AAModule_Menu_Game_Mode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable) void Create_Menu_Main(FName level, TSubclassOf<UUserWidget> m_main, TSubclassOf<UUserWidget> m_button,
		TSubclassOf<UUserWidget> m_option, TSubclassOf<UUserWidget> m_o_button, TSubclassOf<UUserWidget> m_o_tab, TSubclassOf<UUserWidget> m_o_tab_button);
};
//-----------------------------------------------------------------------------------------------------------
