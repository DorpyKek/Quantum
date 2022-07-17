// Quantum.All rights reserved!


#include "GameCore/QuantumPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(StatisticsLog, All, All);

void AQuantumPlayerState::LogInfo()
{
	UE_LOG(StatisticsLog, Warning, TEXT("Team id : %i / Kills : %i / Deaths : %i "), TeamID, Kills, Deaths);
}
