// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DeadHorizon : ModuleRules
{
	public DeadHorizon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"Niagara",
			"NiagaraCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"DeadHorizon",
			"DeadHorizon/Variant_Platforming",
			"DeadHorizon/Variant_Platforming/Animation",
			"DeadHorizon/Variant_Combat",
			"DeadHorizon/Variant_Combat/AI",
			"DeadHorizon/Variant_Combat/Animation",
			"DeadHorizon/Variant_Combat/Gameplay",
			"DeadHorizon/Variant_Combat/Interfaces",
			"DeadHorizon/Variant_Combat/UI",
			"DeadHorizon/Variant_SideScrolling",
			"DeadHorizon/Variant_SideScrolling/AI",
			"DeadHorizon/Variant_SideScrolling/Gameplay",
			"DeadHorizon/Variant_SideScrolling/Interfaces",
			"DeadHorizon/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
