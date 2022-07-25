// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoundFunctionLibrary.generated.h"

class USoundClass;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API USoundFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);

	UFUNCTION(BlueprintCallable)
	static void ToogleSoundClassVolume(USoundClass* SoundClass);
	
};
