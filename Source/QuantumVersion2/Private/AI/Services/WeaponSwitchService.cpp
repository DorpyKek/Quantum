// Quantum.All rights reserved!


#include "AI/Services/WeaponSwitchService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Weapon/WeaponComponent.h"
#include "ComponentGetter.h"

UWeaponSwitchService::UWeaponSwitchService()
{
	NodeName = "Weapon Switch Serviece";
}

void UWeaponSwitchService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = UComponentGetter::GetPlayerComponent<UWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && ChanceToSwitch > 0 && FMath::FRand() <= ChanceToSwitch) 
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}


