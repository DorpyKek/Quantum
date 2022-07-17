// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "BoostPickup.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API ABoostPickup : public ABasePickup
{
	GENERATED_BODY()
	
private:
	
	virtual bool GetPickupInfo(APawn* PlayerPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	float HealthAmount = 30.0f;

};
