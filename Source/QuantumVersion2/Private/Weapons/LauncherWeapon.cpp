// Quantum.All rights reserved!


#include "Weapons/LauncherWeapon.h"
#include "Weapons/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

DECLARE_LOG_CATEGORY_CLASS(LauncherLog, All, All);


void ALauncherWeapon::StartFire()
{
	Super::StartFire();

	if (IsAmmoClipEmpty() || IsAmmoEmpty()) return;

	Shoot();
}

void ALauncherWeapon::Shoot()
{
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();


	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass,SpawnTransform);

	//DrawDebugLine(GetWorld(), TraceStart, Direction, FColor::Red, true,  2.0f);
	
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}

	DecreaseAmmo() ;
	SpawnFX();
	
}
