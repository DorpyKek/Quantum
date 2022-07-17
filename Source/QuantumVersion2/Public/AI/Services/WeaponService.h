// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "WeaponService.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UWeaponService : public UBTService
{
	GENERATED_BODY()

public:
	UWeaponService();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Weapon")
	FBlackboardKeySelector EnemyActorKey;
	
	
};
