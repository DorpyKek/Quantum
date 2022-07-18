// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuantumGameModeBase.h"
#include "TimeRoundWidget.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UTimeRoundWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = "GameInfo")
	int32 GetCurrentTimeInSeconds() const;

	UFUNCTION(BlueprintCallable,Category = "GameInfo")
	int32 GetCurrentTimeInMinutes() const;

	UFUNCTION(BlueprintCallable,Category = "GameInfo")
	int32 GetCurrentRound() const;

	UFUNCTION(BlueprintCallable,Category = "GameInfo")
	int32 GetRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category = "GameInfo")
	bool IsTimeLess10() const;

	UFUNCTION(BlueprintCallable, Category = "GameInfo")
	bool IsFewSeconds() const;

	
	FDataOfGame DataOfGame;
	
};
