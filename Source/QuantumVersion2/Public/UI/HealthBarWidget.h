// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHealthPercent(float Health);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthBar")
	float PercentageVisibility = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthBar")
	float LowPercentageColor = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthBar")
	FLinearColor HealthColor = FLinearColor::Green;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthBar")
	FLinearColor LowHealthColor = FLinearColor::Red;
		

	
};
