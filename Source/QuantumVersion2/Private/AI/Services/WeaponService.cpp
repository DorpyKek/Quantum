// Quantum.All rights reserved!


#include "AI/Services/WeaponService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Weapon/WeaponComponent.h"
#include "ComponentGetter.h"


UWeaponService::UWeaponService()
{
	NodeName = "Fire Service";
}

void UWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasToAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	
	if (Controller)
	{
		const auto WeaponComponent = UComponentGetter::GetPlayerComponent<UWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			HasToAim ? WeaponComponent->StartFire() : WeaponComponent->EndFire();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
