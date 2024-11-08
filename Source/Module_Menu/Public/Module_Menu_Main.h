#pragma once

#include "Module_Menu_Config.h"
#include "Blueprint/UserWidget.h"
#include "Module_Menu_Main.generated.h"

// UAModule_Menu_Option_Button
class UTextBlock;
class UWidgetSwitcher;
class UButton;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class UAModule_Menu_Option_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(const int button_index, UWidgetSwitcher *widget_switcher);

	EModule_Menu_Option_Button_Name Option_Button_Name;
	UWidgetSwitcher *WidgetSwitcher_Tab;  // After pressed need activate tab

	UFUNCTION() void Button_Pressed();  // Handle Module_Menu_Button_State with unique features

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UTextBlock *Button_Text_Block;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UButton *Button_Hitbox;  // Handle Pressed

	static UAModule_Menu_Option_Button *Button_Previous;
};
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Tab_Button
class UTextBlock;
class USlider;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class UAModule_Menu_Tab_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init();  // Don`t update after change settings || Percentage resolution don`t work || Try apply resoultion in setting || Make one func with one switch not 2

	void Button_State_Upate();
	void Get_Button_Tab_State();
	UFUNCTION() void Set_Button_Tab_State(float changed_value);

	EOption_Type Button_Tab_Type;
	FString Slider_Text_Value;
	UGameUserSettings *User_Settings;

	void Toogle_Directx();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UTextBlock *Button_Text_Block;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UTextBlock *Slider_Text_Block;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) USlider *Button_Slider;
};
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Option_Tab
class UTextBlock;
class UVerticalBox;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class UAModule_Menu_Option_Tab : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(const int button_index, TSubclassOf<UUserWidget> tab_button_template);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UTextBlock *Button_Text_Block;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UVerticalBox *VerticalBox_Root;
};
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Main
class UHorizontalBox;
class UWidgetSwitcher;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class UAModule_Menu_Option : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init_Menu_Option(TSubclassOf<UUserWidget> button_template, TSubclassOf<UUserWidget> tab_template, TSubclassOf<UUserWidget> tab_button_template);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget) ) UHorizontalBox *HorizontalBox_Buttons;  // toggle WidgetSwitcher_Tab
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget) ) UWidgetSwitcher *WidgetSwitcher_Tab;  // Switch widgets
};
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Main_Button
class UButton;
class UTextBlock;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class UAModule_Menu_Main_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init();
	
	UUserWidget *Parent_Ptr;
	FName Level_To_Open;  // Used to open new level while pressed on New Game or Continue
	TSubclassOf<UUserWidget> Module_Menu_Option;
	TSubclassOf<UUserWidget> Module_Menu_Option_Button;
	TSubclassOf<UUserWidget> Module_Menu_Option_Tab;
	TSubclassOf<UUserWidget> Module_Menu_Tab_Button;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (ExposeOnSpawn = "true") ) EModule_Menu_Button_State Module_Menu_Button_State;  // Each button has state
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UButton *Button_Hitbox;  // Handle Pressed
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UTextBlock *Button_Text_Block;  // Handle Pressed
	UPROPERTY(Transient, meta = (BindWidgetAnim) ) UWidgetAnimation *Button_Animation_Hovered;  // Described in WBP

private:
	UFUNCTION() void Button_Pressed();  // Handle Module_Menu_Button_State with unique features
	UFUNCTION() void Button_Hovered();  // Handle Animations
	UFUNCTION() void Button_Unhovered();  // Handle Animations
};
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Main
class UVerticalBox;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class MODULE_MENU_API UAModule_Menu_Main : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void Buttons_Menu_Init(const FName &level, const TSubclassOf<UUserWidget> &m_button, const TSubclassOf<UUserWidget> &m_option,
		const TSubclassOf<UUserWidget> &m_o_button, const TSubclassOf<UUserWidget> &m_o_tab, const TSubclassOf<UUserWidget> &m_o_tab_button);  // !!! TEMP

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Store Buttons", meta = (BindWidget) ) UVerticalBox *VerticalBox_Root;

private:
	UAModule_Menu_Main_Button *Button_Menu_Main[(int)EModule_Menu_Button_State::Buttons_Count];  // All Buttons ptrs || can move to func
};
//-----------------------------------------------------------------------------------------------------------
