// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
