// Quantum.All rights reserved!


#include "Components/RespawnComponent.h"
#include "QuantumGameModeBase.h"

URespawnComponent::URespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;
	RespawnCountDown = RespawnTime;

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &URespawnComponent::RespawnTimer, 1.0f, true);
}

bool URespawnComponent::IsRespawning() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void URespawnComponent::RespawnTimer()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
		
		const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;
		
		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}


