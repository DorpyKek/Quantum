// Quantum.All rights reserved!


#include "AI/Services/FindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/CharacterAIPerceptionComponent.h"
#include "ComponentGetter.h"

UFindEnemyService::UFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = UComponentGetter::GetPlayerComponent<UCharacterAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}


