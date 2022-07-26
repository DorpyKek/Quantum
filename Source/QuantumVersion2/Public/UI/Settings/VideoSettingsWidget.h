// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "VideoSettingsWidget.generated.h"
																
class UVerticalBox;
class USettingsOptionWidget;
class UButton;

UCLASS()
class QUANTUMVERSION2_API UVideoSettingsWidget : public UBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VideoSettingsContainer;

	UPROPERTY(meta = (BindWidget))
	UButton* AutoSettingsButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<USettingsOptionWidget> SettingOptionWidgetClass;

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* ReturnButton;

private:
	UFUNCTION()
	void OnAutoSettings();

	UFUNCTION()
	void OnVideoSettingsUpdated();

	UFUNCTION()
	void OnReturnButtonClicked();
};

