// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UVFXComponent;

UCLASS()
class QUANTUMVERSION2_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }
	
	

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float DamageRadius = 200.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProjectileDamage = 40.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	bool DoFullDamage = false;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	UVFXComponent* WeaponVFXComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float LifeSeconds = 4.0f;
	

private:
	
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;
};
