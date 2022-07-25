// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

class UWidgetAnimation;
class USoundCue;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();
		
protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* WidgetOpenSound;
	
};
