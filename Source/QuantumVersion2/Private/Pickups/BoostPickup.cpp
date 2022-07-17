// Quantum.All rights reserved!


#include "Pickups/BoostPickup.h"
#include "Components/HealthComponent.h"
#include "Weapon/WeaponComponent.h"
DEFINE_LOG_CATEGORY_STATIC(HealthPickLog, All, All);




bool ABoostPickup::GetPickupInfo(APawn* PlayerPawn)
{
	const auto HealthComponent = PlayerPawn->FindComponentByClass<UHealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = PlayerPawn->FindComponentByClass<UWeaponComponent>();
	if (!WeaponComponent) return false;

	return HealthComponent->HealPlayerFromPick(HealthAmount);

	UE_LOG(HealthPickLog,Error,TEXT("Boost has been picked up"));
    return true;
}
