#pragma once

#include "Module_Menu_Config.h"
#include "Blueprint/UserWidget.h"
#include "Module_Menu_Main.generated.h"

// UAModule_Menu_Option_Button_Switcher
class UWidgetSwitcher;
class UTextBlock;
class UButton;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class UAModule_Menu_Option_Button_Switcher : public UUserWidget
{// 
	GENERATED_BODY()

public:
	void Create_Button(const int button_index, UWidgetSwitcher *widget_switcher);

	EModule_Menu_Option_Button_Tabs Button_Switcher_State_Index;
	UWidgetSwitcher *WidgetSwitcher_Tab;  // After pressed need activate tab

	static UAModule_Menu_Option_Button_Switcher *Button_Previous;

	UPROPERTY(meta = (BindWidget) ) UButton *Button_Hitbox;  // Handle Pressed

private:
	UFUNCTION() void Button_Pressed();  // Handle Module_Menu_Button_State with unique features

	UPROPERTY(meta = (BindWidget) ) UTextBlock *Button_Text_Block;
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
	void Button_Setting_Setup();  // Don`t update after change settings || Percentage resolution don`t work || Try apply resoultion in setting || Make one func with one switch not 2

	EOption_Type Button_Tab_Type;

private:
	void Get_Tab_Buttons_Settings();  // Use EOption_Type to have unique feature
	void Set_Tab_Buttons_Settings(const float changed_value);  // Update setting state
	void Slider_Text_Block_Update(const int button_index);
	void Toogle_Directx();

	UGameUserSettings *User_Settings;
	FString Slider_Text_Value;

	UFUNCTION() void Button_Slider_Value_Changed(const float changed_value);  // Update setting state

	UPROPERTY(meta = (BindWidget) ) UTextBlock *Button_Text_Block;  // Show curr setting names
	UPROPERTY(meta = (BindWidget) ) UTextBlock *Slider_Text_Block;  // Show curr setting param
	UPROPERTY(meta = (BindWidget) ) USlider *Button_Slider;
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
	void Create_Tab(const int button_index, TSubclassOf<UUserWidget> tab_button_template);  // Create buttons in tabs & Must be before add | Or not all setting apply to Slider

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UTextBlock *Button_Text_Block;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UVerticalBox *Vertical_Box_Tab_Buttons;
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
	void Create_Menu_Option(TSubclassOf<UUserWidget> button_switcher_template, TSubclassOf<UUserWidget> tab_widget_template, TSubclassOf<UUserWidget> tab_button_template);  // button tab ( tab switcher ) | tab template ( stored tab button templates )

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget) ) UHorizontalBox *Horizontal_Box_Buttons;  // toggle WidgetSwitcher_Tab
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget) ) UWidgetSwitcher *Widget_Switcher_Tab;  // Switch widgets
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
	void Create_Button(const EModule_Menu_Main_Button_State menu_button_state);
	
	EModule_Menu_Main_Button_State Module_Menu_Button_State;  // Each button has unique state
	UUserWidget *Parent_Ptr;  // Ptr to parent class, useing to remove parent from viewport and destroy all created widget
	FName Level_To_Open;  // Used to open new level while pressed on New Game or Continue

	// !!! Make array of subclass?
	TSubclassOf<UUserWidget> Module_Menu_Option;
	TSubclassOf<UUserWidget> Module_Menu_Option_Button_Switcher;
	TSubclassOf<UUserWidget> Module_Menu_Option_Tab_Widget;
	TSubclassOf<UUserWidget> Module_Menu_Option_Tab_Button;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UButton *Button_Hitbox;  // Binded in Child of those class
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UTextBlock *Button_Text_Block;  // Handle Pressed
	UPROPERTY(Transient, meta = (BindWidgetAnim) ) UWidgetAnimation *Button_Animation_Hovered;  // Described in WBP

private:
	UFUNCTION() void Button_Pressed();  // Handle Module_Menu_Button_State with unique features
	UFUNCTION() void Button_Hovered();  // Play animation in WBP from 0 to 1
	UFUNCTION() void Button_Unhovered();  // Play animation in WBP from 1 to 0
};
//-----------------------------------------------------------------------------------------------------------




// UAModule_Menu_Main
class UVerticalBox;
//-----------------------------------------------------------------------------------------------------------
UCLASS(meta = (DisableNativeTick) ) class MODULE_MENU_API UAModule_Menu_Main : public UUserWidget
{
	GENERATED_BODY()

public:
	void Buttons_Menu_Init(const FName &level, const TSubclassOf<UUserWidget> &m_button, const TSubclassOf<UUserWidget> &m_option, const TSubclassOf<UUserWidget> &m_o_button, const TSubclassOf<UUserWidget> &m_o_tab, const TSubclassOf<UUserWidget> &m_o_tab_button);  // !!! TEMP

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Store Buttons", meta = (BindWidget) ) UVerticalBox *VerticalBox_Root;

private:
	UAModule_Menu_Main_Button *Menu_Button_Array[(int)EModule_Menu_Main_Button_State::Count];  // All Buttons ptrs || can move to func
};
//-----------------------------------------------------------------------------------------------------------
