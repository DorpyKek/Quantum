// Quantum.All rights reserved!


#include "Weapons/M16Weapon.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Weapons/Components/VFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "DrawDebugHelpers.h"



AM16Weapon::AM16Weapon()
{
	VFXComponent = CreateDefaultSubobject<UVFXComponent>("VFXComponent");
}

void AM16Weapon::StartFire() {
	GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &AM16Weapon::Shoot, TimeBetweenShots, true);
	Shoot();
	InitializeMuzzleFX();
}

void AM16Weapon::StopFire() {
	GetWorld()->GetTimerManager().ClearTimer(ShootTimerHandle);
	SetFXVisibility(false);
	
	
	
}

void AM16Weapon::Shoot()
{
	if (!GetWorld() || IsAmmoClipEmpty()) return;

	const auto Player = Cast<ACharacter>(GetOwner());

	if (!Player) return;

	//creating player controller
	const auto PlayerController = Player->GetController();

	if (!PlayerController) return;

	FVector ViewLocation;
	FRotator ViewRotation;

	PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	const FVector TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	const FVector TraceEnd = TraceStart + ShootDirection * MaxShootDistance;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = true;


	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,CollisionParams);


	FVector TraceFXEnd = TraceEnd;
		
	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;
		
		VFXComponent->PlayFireFX(HitResult);
		
		if (HitResult.GetActor())
		{
			Hitted = true;
			HitResult.GetActor()->TakeDamage(Damage, FDamageEvent(), GetController(), this);	
		}
	}
	
	SpawnTrace(WeaponMesh->GetSocketLocation(MuzzleSocketName), TraceFXEnd);
	DecreaseAmmo();

}

void AM16Weapon::BeginPlay()
{
	Super::BeginPlay();
	check(VFXComponent);
	
}

void AM16Weapon::InitializeMuzzleFX()
{
	if(!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnFX();
	}
	SetFXVisibility(true);
}

void AM16Weapon::SetFXVisibility(bool Visible)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!Visible);
		MuzzleFXComponent->SetVisibility(Visible, true);
	}
}

void AM16Weapon::SpawnTrace(const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!TraceFX) return;

	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
	
	if (TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceFXName,TraceEnd);
	}
}


AController* AM16Weapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;



}

