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

	UPROPERTY(meta = (BindWidget) ) UButton *Button_Hitbox;  // Handle Pressed
	
	static UAModule_Menu_Option_Button_Switcher *Button_Previous;

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
	void Button_Setting_Setup();  // Starting point

	EOption_Type Button_Tab_Type;

private:
	void Get_Tab_Buttons_Settings();  // Use EOption_Type to have unique feature | Initialize Slider value
	void Set_Tab_Buttons_Settings(const float changed_value);  // Update setting state
	void Set_Slider_Text_Block(const int button_index);  // Set unique text to slider text block use Slider Text Value
	void Tab_Buttons_Quality_Redraw() const;  // Update all quality tab button while change presset
	void DirectX_Switcher() const;

	UFUNCTION() void Button_Slider_Value_Changed(const float changed_value);  // Update setting state
	UFUNCTION() void Settings_Apply();  // Apply and save settings to config

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
	void Create_Tab(EModule_Menu_Option_Button_Tabs tab_button, TSubclassOf<UUserWidget> &tab_button_template);  // Create buttons in tabs & Must be before add | Or not all setting apply to Slider

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
	void Create_Menu_Option(TArray<TSubclassOf<UUserWidget> > *widget_type);

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
	void Set_Button_Focus();

	EModule_Menu_Main_Button_State Module_Menu_Button_State;  // Each button has unique state
	FName Level_To_Open;  // Used to open new level while pressed on New Game or Continue
	UUserWidget *Parent_Ptr;  // Ptr to parent class, using to remove parent from viewport and destroy all created widget
	TArray<TSubclassOf<UUserWidget> > *Widget_Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UButton *Button_Hitbox;  // bind in Child of those class
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UTextBlock *Button_Text_Block;  // Handle Pressed
	UPROPERTY(Transient, meta = (BindWidgetAnim) ) UWidgetAnimation *Button_Animation_Hovered;  // Described in WBP

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
	UFUNCTION(BlueprintCallable, Category = "Init") void Create_Menu_Main(const bool is_continue_button);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Init", meta = (ExposeOnSpawn = "true") ) FName New_Game_Level_Open_Name;
	UPROPERTY(EditAnywhere, Category = "Init", meta = (ToolTip = "M_Main | M_Button | M_Option | MO_Button | Tab | T_Button") ) TArray<TSubclassOf<UUserWidget> > Module_Widgets;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init", meta = (BindWidget) ) UVerticalBox *Vertical_Box_Menu_Buttons;
};
//-----------------------------------------------------------------------------------------------------------

#pragma region TASKS
/*
	X - Store ptr to all buttons in menu
*/
#pragma endregion
