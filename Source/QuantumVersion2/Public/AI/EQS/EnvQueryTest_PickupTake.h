// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupTake.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UEnvQueryTest_PickupTake : public UEnvQueryTest
{
	GENERATED_BODY()
public:
	UEnvQueryTest_PickupTake(const FObjectInitializer& ObjectInitializer);
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
};
