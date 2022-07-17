// Quantum.All rights reserved!

using UnrealBuildTool;
using System.Collections.Generic;

public class QuantumVersion2Target : TargetRules
{
	public QuantumVersion2Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "QuantumVersion2" } );
	}
}
