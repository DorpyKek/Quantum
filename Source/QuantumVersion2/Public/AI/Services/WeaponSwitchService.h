// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "WeaponSwitchService.generated.h" 

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UWeaponSwitchService : public UBTService
{
	GENERATED_BODY()
public:
	UWeaponSwitchService();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "0.0",ClampMax = "1.0"))
	float ChanceToSwitch = 0.5f;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
	
