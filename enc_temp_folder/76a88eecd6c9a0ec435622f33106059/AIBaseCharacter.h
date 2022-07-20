// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "QuantumBaseCharacter.h"
#include "AIBaseCharacter.generated.h"


class UBehaviorTree;
class UWidgetComponent;
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
	virtual void BeginPlay() override;

	virtual void OnHealthChanged(float Health, float DeltaHealth) override;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthBar")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthBar")
	float HealtVisibilityPercentageDistance = 1200.0f;

private:
	void UpdateHeatlhWidgetVisibility();
	
	
};
