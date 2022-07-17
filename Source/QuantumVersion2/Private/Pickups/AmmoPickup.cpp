// Quantum.All rights reserved!


#include "Pickups/AmmoPickup.h"
#include "Components/HealthComponent.h"
#include "Weapon/WeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(AmmoPickLog, All, All);


bool AAmmoPickup::GetPickupInfo(APawn* PlayerPawn)
{
	const auto HealthComponent = PlayerPawn->FindComponentByClass<UHealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead()) return false;
	
	const auto WeaponComponent = PlayerPawn->FindComponentByClass<UWeaponComponent>();
	if (!WeaponComponent) return false;
	
	return WeaponComponent->GiveAmmo(TypeOfWeapon, AmmoAmount);




	

	UE_LOG(AmmoPickLog,Warning,TEXT("Ammo has been picked up"));
    return true;
}
