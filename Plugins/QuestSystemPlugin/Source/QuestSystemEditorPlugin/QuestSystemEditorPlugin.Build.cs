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
				"QuestSystemPlugin",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"BlueprintGraph",
			}
			);
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
