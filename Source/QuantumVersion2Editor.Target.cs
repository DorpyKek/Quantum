// Quantum.All rights reserved!

using UnrealBuildTool;
using System.Collections.Generic;

public class QuantumVersion2EditorTarget : TargetRules
{
	public QuantumVersion2EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "QuantumVersion2" } );
	}
}
