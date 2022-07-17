// Quantum.All rights reserved!


#include "Weapon/AIWeaponComponent.h"
#include "Weapons/RiffleWeapon.h "

void UAIWeaponComponent::StartFire()
{
	if (!CanFire()) return;
	
	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void UAIWeaponComponent::NextWeapon()
{
	if (!CanSwap()) return;
	
	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

	while (NextIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}
