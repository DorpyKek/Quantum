// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MarkerWidget.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UMarkerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Hitmarker")
	bool IsHitted();
	
};
