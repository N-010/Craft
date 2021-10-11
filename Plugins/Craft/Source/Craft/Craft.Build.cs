// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Craft : ModuleRules
{
	public Craft(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		var modulePublic = string.Format(ModuleDirectory + "/Public");
		var modulePrivate = string.Format(ModuleDirectory + "/Private");

		PublicIncludePaths.AddRange(
			new string[]
			{
				modulePublic,
			}
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
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
				"Json",
				"JsonUtilities",
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}