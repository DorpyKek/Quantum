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

	
		

private:

	UPROPERTY()
	TArray<ULevelSelectorWidget*>LevelSelectorWidgets;

	void CreateLevelItems();

	void OnLevelSelected(const FLevelData& Data);

	UQuantumGameInstance* GetMyGameInstance() const;
	
	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();
	
};
