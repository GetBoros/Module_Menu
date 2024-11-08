#include "Module_Menu_Config.h"

// AsModule_Menu_Config
const FIntPoint AsModule_Menu_Config::Screen_Resolution_Array[AsModule_Menu_Config::Button_Setting_Count] = { {960, 540}, {1280, 720}, {1920, 1080}, {2560, 1440}, {3840, 2160} };
const FName AsModule_Menu_Config::Button_Name_Defaults[Button_Setting_Count] = { L"1", L"2", L"3", L"4", L"5" };
//------------------------------------------------------------------------------------------------------------
AsModule_Menu_Config::~AsModule_Menu_Config()
{
}
//------------------------------------------------------------------------------------------------------------
AsModule_Menu_Config::AsModule_Menu_Config()
{
}
//------------------------------------------------------------------------------------------------------------
void AsModule_Menu_Config::Throw()
{
	return throw 13;
}
//------------------------------------------------------------------------------------------------------------
