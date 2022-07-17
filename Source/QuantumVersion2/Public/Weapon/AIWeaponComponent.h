// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponComponent.h"
#include "AIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UAIWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()

public:
	
	virtual void StartFire() override;
	virtual void NextWeapon() override;
	
};
