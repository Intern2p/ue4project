// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ue4Project : ModuleRules
{
	public ue4Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
