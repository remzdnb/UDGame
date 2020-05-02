using UnrealBuildTool;
using System.Collections.Generic;

public class UDGameTarget : TargetRules
{
	public UDGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("UDGame");
		ExtraModuleNames.Add("UDCombatModule");
		//ExtraModuleNames.Add("UDCampaignModule");
	}
}
