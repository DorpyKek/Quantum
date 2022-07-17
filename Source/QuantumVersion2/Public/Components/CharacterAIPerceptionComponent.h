// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "CharacterAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UCharacterAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	AActor* GetClosestEnemy() const;
	
};
