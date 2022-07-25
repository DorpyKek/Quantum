// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Weapons/RiffleWeapon.h"
#include "M16Weapon.generated.h"


class UVFXComponent;
class UCameraShakeBase;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API AM16Weapon : public ARiffleWeapon
{
	GENERATED_BODY()

public:
	
	AM16Weapon();
	
	virtual void StartFire() override;
	virtual void StopFire() override;
	virtual void Zoom(bool Enabled) override;

	bool Hitted = false;

protected:
	virtual void Shoot() override;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UVFXComponent* VFXComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	FString TraceFXName = "TraceTarget";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TSubclassOf<UCameraShakeBase> ShootCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
	UAudioComponent* FireAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FOV")
	float FOVAngle = 60.0f;
	


	//creating beginplay function
	virtual void BeginPlay() override;
	
	
private:
	FTimerHandle ShootTimerHandle;


	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;

	void InitFX();
	
	void SetFXActive(bool IsActive);

	void SpawnTrace(const FVector& TraceStart, const FVector& TraceEnd);

	AController* GetController() const;

	float DefaultCameraFOV = 90.0f;

	
};
