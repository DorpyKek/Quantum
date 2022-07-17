// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance,FEnvQueryContextData& ContextData) const override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName EnemyActorKeyName = "EnemyActor";
		
	
};
