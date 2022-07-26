// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "QuantumGameModeBase.h"
#include "UI/BaseWidget.h"
#include "PauseWidget.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UPauseWidget : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	
protected:
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
		

private:
	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void ReturnToMainMenu();

	UFUNCTION()
	void OpenSettings();
};
