// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

private:
	
	UFUNCTION()
	void StartGame();
	
};
