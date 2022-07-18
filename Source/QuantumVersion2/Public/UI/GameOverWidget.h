// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuantumGameModeBase.h"
#include "GameOverWidget.generated.h"

class UVerticalBox;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Over widget")
	TSubclassOf<UUserWidget> PlayerStatisticsRowWidget;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

private:
	void OnMatchStateChanged(EQuantumMatchState State);
	void UpdatePlayerStatistics();
	
};
