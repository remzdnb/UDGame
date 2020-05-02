using UnrealBuildTool;

public class UDCombatModule : ModuleRules
{
    public UDCombatModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
 
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "UDGame"
            });
    }
}