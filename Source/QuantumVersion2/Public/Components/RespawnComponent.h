// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUANTUMVERSION2_API URespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URespawnComponent();
	
	void Respawn(int32 RespawnTime);
	
	int32 GetRespawnTimer() const { return RespawnCountDown; }

	bool IsRespawning() const;
	
	
private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;
	
	void RespawnTimer();
	
};
