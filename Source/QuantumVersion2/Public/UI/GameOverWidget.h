// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "QuantumGameModeBase.h"
#include "UI/BaseWidget.h"
#include "GameOverWidget.generated.h"

class UVerticalBox;
class UButton;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UGameOverWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Over widget")
	TSubclassOf<UUserWidget> PlayerStatisticsRowWidget;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChanged(EQuantumMatchState State);
	void UpdatePlayerStatistics();

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void ReturnToMainMenu();

	
	
};
