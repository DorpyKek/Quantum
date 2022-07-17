// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HealthDecorator.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UHealthDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UHealthDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthPercent = 0.5f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
