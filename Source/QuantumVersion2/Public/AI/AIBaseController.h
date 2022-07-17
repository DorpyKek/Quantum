 // Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIBaseController.generated.h"

class UCharacterAIPerceptionComponent;
class URespawnComponent;

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API AAIBaseController : public AAIController
{
	GENERATED_BODY()
public:
	AAIBaseController();
		
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "AI")
	UCharacterAIPerceptionComponent* CharacterPercreptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	URespawnComponent* RespawnComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	FName FocusKeyName = "EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;

	//creating tick function 
	virtual void Tick(float DeltaTime) override;
private:
	AActor* GetFocusedActor() const;
	
	
};
