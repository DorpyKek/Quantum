// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "AmmoPickup.generated.h"


class ARiffleWeapon;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "7.0"))
	int32 AmmoAmount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
		TSubclassOf<ARiffleWeapon> TypeOfWeapon;

private:
	virtual bool GetPickupInfo(APawn* PlayerPawn) override;

	
};
