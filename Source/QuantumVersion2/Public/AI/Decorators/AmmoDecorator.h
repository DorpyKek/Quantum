// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Weapons/RiffleWeapon.h"
#include "AmmoDecorator.generated.h"

class ARiffleWeapon;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
		
public:
	UAmmoDecorator();
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Ammo")
	TSubclassOf<ARiffleWeapon>WeaponClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoNeedForSearching = 3;
	
};
