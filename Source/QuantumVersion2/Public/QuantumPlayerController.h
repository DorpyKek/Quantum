// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QuantumBaseCharacter.h"
#include "QuantumGameModeBase.h"
#include "UI/PauseWidget.h"
#include "QuantumPlayerController.generated.h"

class URespawnComponent;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API AQuantumPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AQuantumPlayerController();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RespawnComponent")
	URespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* NewPawn) override;

	virtual void SetupInputComponent() override;
	

private:
	void OnGamePaused();


	void OnMatchStateChanged(EQuantumMatchState State);
	
	
};
