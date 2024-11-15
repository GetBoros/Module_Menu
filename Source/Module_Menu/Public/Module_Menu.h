#pragma once

#include "CoreMinimal.h"

// Tutorials
/*
	- Class Naming Prefix :
		- A : AActor - Spawnable actor can be spawned in the world
		- U : UComponent - Extended from base class A, can`t be directly instanced to the world

	- UCLASS() macro :
		- auto include the class declaration, constructor
		- At the top of each gameplay class header :
			- #include "Module_Menu_Game_Mode.generated.h"
		- Must be placed at the very beginning of the class body :
			- GENERATED_BODY() : Used to be implemented properly

	- Class Specifier :
		- Example : UCLASS(Abstract, meta = )
			- (Abstract, AdvancedClassDisplay, AutoCollapseCategories=(cat1, cat2, ...), AutoExpandCategories=(Cat, cat2, ...), Blueprintable, BlueprintType, MinimalAPI, Const, Config=ConfigName
		- Example : Metadata Specifiers :
			- BlueprintSpawnableComponent, BlueprintThreadSafe, ChildCannotTick, 
			


*/