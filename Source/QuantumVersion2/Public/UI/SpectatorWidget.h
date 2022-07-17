// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API USpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = "Respawn")
	bool GetRespawnTimer (int32& CountdownTime);
	
};
