// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "QuantumGameModeBase.h"
#include "GameHUD.generated.h"


/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
		virtual void DrawHUD() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	//creaiting begin play
	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY()
	TMap<EQuantumMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;

	void DrawCross();

	void OnMatchStateChanged(EQuantumMatchState State);

};
