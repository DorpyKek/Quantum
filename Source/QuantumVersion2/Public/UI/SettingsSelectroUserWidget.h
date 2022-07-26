// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "SettingsSelectroUserWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API USettingsSelectroUserWidget : public UBaseWidget
{
	GENERATED_BODY()
		
protected:

	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* VideoSettingsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AudioSettingsButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BackToPauseButton;
	

private:
	
	UFUNCTION()
	void OnVideoSettingsButtonClicked();
	
	UFUNCTION()
	void OnAudioSettingsButtonClicked();
	
	UFUNCTION()
	void OnBackToPauseButtonClicked();

};
