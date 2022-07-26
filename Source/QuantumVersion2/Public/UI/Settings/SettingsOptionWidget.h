// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsOptionWidget.generated.h"

class UTextBlock;
class UQuantumGameSetting;
class UButton;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API USettingsOptionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SettingDisplayName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SettingCurrentValue;

	UPROPERTY(meta = (BindWidget))
	UButton* NextSettingButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* PreviousSettingButton;

	virtual void NativeOnInitialized() override;

private:
	TWeakObjectPtr<UQuantumGameSetting> Setting;

	void Init(UQuantumGameSetting* Setting);
	
	void UpdateText();

	UFUNCTION()
	void OnNextSetting();

	UFUNCTION()
	void OnPrevSetting();

	friend class UVideoSettingsWidget;
	
};
