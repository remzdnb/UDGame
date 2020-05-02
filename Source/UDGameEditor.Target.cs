using UnrealBuildTool;
using System.Collections.Generic;

public class UDGameEditorTarget : TargetRules
{
	public UDGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("UDGame");
		ExtraModuleNames.Add("UDCombatModule");
		//ExtraModuleNames.Add("UDCampaignModule");
	}
}
