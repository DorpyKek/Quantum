// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "QuantumBaseCharacter.h"
#include "AIBaseCharacter.generated.h"


class UBehaviorTree;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API AAIBaseCharacter : public AQuantumBaseCharacter
{
	GENERATED_BODY()

public:
	AAIBaseCharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI")
	UBehaviorTree* BehaviorTree;

	virtual void OnDeath() override;
	
	
};
