// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "QuantumGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UQuantumGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FName GetStartupLevel() const { return StartLevelName; }

	FName GetMainMenuLevel() const { return MenuLevelName; }
protected:
	UPROPERTY(EditDefaultsOnly,Category = "Game Instance")
	FName StartLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game Instance")
	FName MenuLevelName = NAME_None;
	
};
