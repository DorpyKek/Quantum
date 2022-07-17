// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NextLocation.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UNextLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UNextLocation();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Radius = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector AimLocationKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool SelfCenter = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"));
	FBlackboardKeySelector CenterActorKey;

	
};
	
