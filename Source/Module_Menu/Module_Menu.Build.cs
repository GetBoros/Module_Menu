using UnrealBuildTool;

public class Module_Menu : ModuleRules
{
	public Module_Menu(ReadOnlyTargetRules Target) : base(Target)  // Make visible to Unreal build system
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
