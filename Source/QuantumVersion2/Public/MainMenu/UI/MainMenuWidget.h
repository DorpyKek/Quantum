// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "MainMenu/UI/LevelSelectorWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UQuantumGameInstance;
class ULevelSelectorWidget;
class UWidgetAnimation;
class UTextBlock;
class USoundCue;
class UVideoSettingsWidget;
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

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelSelectorBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	TSubclassOf<UUserWidget>LevelItemClass;

	UPROPERTY(meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* QuitAnimation;

	UPROPERTY(meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* LoadAnimation;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitGameTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* StartGameSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* OpenWidgetSound;

	FTimerHandle AnimationTimerHandle;

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

private:

	UPROPERTY()
	TArray<ULevelSelectorWidget*>LevelSelectorWidgets;
	

	void CreateLevelItems();

	void OnLevelSelected(const FLevelData& Data);

	UQuantumGameInstance* GetMyGameInstance() const;

	void VisibilityShow();

	void VisibilityClose();
	
	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();

	UFUNCTION()
	void OpenSettings();

	UPROPERTY()
	UVideoSettingsWidget* VideoSettingsWidget;
	
};
