// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "QuantumGameModeBase.h"
#include "QuantumPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API AQuantumPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void SetTeamId(int32 ID) { TeamID = ID; }
	int32 GetTeamId() const { return TeamID; }

	void SetColorOfTeam(FLinearColor Color) { ColorOfTeam = Color; }
	FLinearColor GetColorOfTeam() const { return ColorOfTeam; }

	void AddKill() { ++Kills; }
	int32 GetKills() const { return Kills; }

	void AddDeath() { ++Deaths; }
	int32 GetDeaths() const { return Deaths; }

	void LogInfo();

private:
	int32 TeamID;
	FLinearColor ColorOfTeam;

	int32 Kills;
	int32 Deaths;
	
};
