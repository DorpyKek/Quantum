// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "QuantumGameModeBase.h"
#include "PauseWidget.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	
protected:
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	UButton* ResumeButton;
	
	
	

private:
	UFUNCTION()
	void ResumeGame();
};
