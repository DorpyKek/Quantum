// Quantum.All rights reserved!


#include "Weapons/M16Weapon.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Weapons/Components/VFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "DrawDebugHelpers.h"
#include "Components/AudioComponent.h"



AM16Weapon::AM16Weapon()
{
	VFXComponent = CreateDefaultSubobject<UVFXComponent>("VFXComponent");
}

void AM16Weapon::StartFire() {
	GetWorld()->GetTimerManager().SetTimer(ShootTimerHandle, this, &AM16Weapon::Shoot, TimeBetweenShots, true);
	Shoot();
	InitFX();
}

void AM16Weapon::StopFire() {
	GetWorld()->GetTimerManager().ClearTimer(ShootTimerHandle);
	SetFXActive(false);
	
}

void AM16Weapon::Zoom(bool Enabled)
{
	const auto Controller = Cast<APlayerController>(GetController());
	if (!Controller || !Controller->PlayerCameraManager) return;
	
	if (Enabled)
	{
		DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
	}

	const TInterval <float> FOV(60.0f, 90.0f);
	Controller->PlayerCameraManager->SetFOV(Enabled ? FOVAngle : DefaultCameraFOV);
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
		
		FPointDamageEvent PointDamageEvent;
		PointDamageEvent.HitInfo = HitResult;

		if (HitResult.GetActor())
		{
			HitResult.GetActor()->TakeDamage(Damage, PointDamageEvent, GetController(), this);	
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

void AM16Weapon::InitFX()
{
	if(!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnFX();
	}

	if(!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(ShotSoundCue, WeaponMesh, MuzzleSocketName);
	}

	SetFXActive(true);
}

void AM16Weapon::SetFXActive(bool IsActive)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!IsActive);
		MuzzleFXComponent->SetVisibility(IsActive, true);
	}

	if (FireAudioComponent)
	{
		FireAudioComponent->SetPaused(!IsActive);
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

