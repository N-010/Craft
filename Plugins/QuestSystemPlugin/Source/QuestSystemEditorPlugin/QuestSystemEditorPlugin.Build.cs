// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class QuestSystemEditorPlugin : ModuleRules
{
	public QuestSystemEditorPlugin(ReadOnlyTargetRules Target) : base(Target)
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
		
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"UnrealEd",
				});
		}
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
