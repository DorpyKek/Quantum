// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/BaseWidget.h"
#include "SpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API USpectatorWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = "Respawn")
	bool GetRespawnTimer (int32& CountdownTime);
	
};
