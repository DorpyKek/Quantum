// Quantum.All rights reserved!


#include "AI/EQS/EnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void UEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	const auto BlackboardComp = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (!BlackboardComp) return;
	const auto ContextActor = BlackboardComp->GetValueAsObject(EnemyActorKeyName);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
}
