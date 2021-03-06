// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "QuantumGameModeBase.h"
#include "GameHUD.generated.h"

class UBaseWidget;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> SettingsWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> VideoSettingsWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> AudioSettingsWidget;

	//creaiting begin play
	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY()
	TMap<EQuantumMatchState, UBaseWidget*> GameWidgets;

	UPROPERTY()
	UBaseWidget* CurrentWidget = nullptr;

	void DrawCross();

	void OnMatchStateChanged(EQuantumMatchState State);

};
