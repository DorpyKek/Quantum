// Quantum.All rights reserved!


#include "AI/Decorators/AmmoDecorator.h"
#include "AIController.h"
#include "Weapon/WeaponComponent.h"
#include "ComponentGetter.h"

UAmmoDecorator::UAmmoDecorator()
{
	NodeName = "Ammo Finder";
}

bool UAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto WeaponComponent = UComponentGetter::GetPlayerComponent<UWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent) return false;
	
	return WeaponComponent->NeedAmmo(WeaponClass);
}
