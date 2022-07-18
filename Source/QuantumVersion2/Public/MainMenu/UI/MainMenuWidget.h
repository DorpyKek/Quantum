// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UMainMenuWidget : public UBaseWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

private:
	
	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();
	
};
