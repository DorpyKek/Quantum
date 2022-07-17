// Quantum.All rights reserved!


#include "UI/SpectatorWidget.h"
#include "Components/RespawnComponent.h"
#include "ComponentGetter.h"

bool USpectatorWidget::GetRespawnTimer(int32& CountdownTime)
{
	const auto RespawnComponent = UComponentGetter::GetPlayerComponent<URespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent || !RespawnComponent->IsRespawning()) return false;

	CountdownTime = RespawnComponent->GetRespawnTimer();
	return true;
}
