// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Weapons/RiffleWeapon.h"
#include "LauncherWeapon.generated.h"

class AProjectile;

UCLASS()
class QUANTUMVERSION2_API ALauncherWeapon : public ARiffleWeapon
{
	GENERATED_BODY()

private:
	
	virtual void StartFire() override;
	
protected:
	//creating class of our projectile
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AProjectile> ProjectileClass;
	
	virtual void Shoot() override;
	
};
