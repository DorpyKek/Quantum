// Quantum.All rights reserved!


#include "Weapons/RiffleWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "QuantumGameModeBase.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Weapons/RiffleWeapon.h"

DECLARE_LOG_CATEGORY_CLASS(FireLog, All, All);

// Sets default values
ARiffleWeapon::ARiffleWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}



bool ARiffleWeapon::GiveAmmo(int32 ClipsAmount)
{
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

	if(IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if(CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipAmount = CurrentAmmo.Clips + ClipsAmount;
		if(DefaultAmmo.Clips - NextClipAmount >= 0)
		{
			CurrentAmmo.Clips = NextClipAmount;
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;																	
		}
	}
	else
	{
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}
	
	return true;
}

void ARiffleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check (WeaponMesh);

	CurrentAmmo = DefaultAmmo;

}

void ARiffleWeapon::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0) return; 
	
	CurrentAmmo.Bullets--;
	LogAmmo();

	if (IsAmmoClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}
}

bool ARiffleWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsAmmoClipEmpty();
}

bool ARiffleWeapon::IsAmmoClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

void ARiffleWeapon::ChangeClip()
{	
	if(!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0) return; 
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	//UE_LOG(FireLog,Error,TEXT("Reloading..."))
}

bool ARiffleWeapon::CanReload()
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

void ARiffleWeapon::LogAmmo()
{
	FString AmmoString = FString::FromInt(CurrentAmmo.Bullets) + " / " ;
	AmmoString += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	//UE_LOG(FireLog, Warning, TEXT("%s"), *AmmoString);
}

UNiagaraComponent* ARiffleWeapon::SpawnFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,
		WeaponMesh,
		MuzzleSocketName,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget,
		true);
}

bool ARiffleWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}



bool ARiffleWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (!PlayerCharacter) return false;

	if (PlayerCharacter->IsPlayerControlled())
	{
		const auto Controller = PlayerCharacter->GetController<APlayerController>();
		if (!Controller) return false;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}

	return true;
}

FVector ARiffleWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

void ARiffleWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.bReturnPhysicalMaterial = true;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

bool ARiffleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = GetMuzzleWorldLocation();
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * MaxShootDistance;
	return true;
}

void ARiffleWeapon::StartFire() 
{
	
}

void ARiffleWeapon::StopFire() 
{
	
}

void ARiffleWeapon::Shoot()
{
	
}






