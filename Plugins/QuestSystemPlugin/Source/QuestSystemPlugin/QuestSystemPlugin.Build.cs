// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class QuestSystemPlugin : ModuleRules
{
	public QuestSystemPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		var modulePublic = string.Format(ModuleDirectory + "/Public");
		var modulePrivate = string.Format(ModuleDirectory + "/Private");
		
		PublicIncludePaths.AddRange(
			new string[] {
				modulePublic,
			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				modulePrivate,
			}
		);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
