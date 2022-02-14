// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class distance : ModuleRules
{
	public distance(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay",
			"NavigationSystem", 
			"AIModule",
			"UMG",
			"Inventory",		
			"DesktopPlatform"
		});


		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
		});
    }
}
