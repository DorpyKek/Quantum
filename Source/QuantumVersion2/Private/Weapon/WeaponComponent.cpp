// Quantum.All rights reserved!


#include "Weapon/WeaponComponent.h"
#include "Weapons/RiffleWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/ReloadAnimNotify.h"
#include "Components/HealthComponent.h"
#include "QuantumGameModeBase.h"
#include "QuantumBaseCharacter.h"
#include "Animations/EquipAnimNotify.h"

//creating log category for debugging
DEFINE_LOG_CATEGORY_STATIC(WeaponLog, All, All);

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
	
	InitAnimations();

	SpawnWeapons();
	
	EquipWeapon(CurrentWeaponIndex);
	
	IsNextWeapon = false;
}



void UWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ARiffleWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &UWeaponComponent::OnEmptyClip);

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void UWeaponComponent::AttachWeaponToSocket(ARiffleWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num()) return;
	
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if(CurrentWeapon)
	{
		CurrentWeapon->Zoom(false);
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	
	CurrentWeapon = Weapons[WeaponIndex];
	//CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimations;
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) { return Data.WeaponClass == CurrentWeapon->GetClass(); });
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimations : nullptr;	
	
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	AnimationChange = true;
	
	PlayAnimMontage(EquipAnimMontage);
}



void UWeaponComponent::NextWeapon()
{
	if (!CanSwap()) return;
	
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
	AnimationUI();
}

void UWeaponComponent::Reload()
{
	ChangeClip();
}

bool UWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

bool UWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}




void UWeaponComponent::StartFire()
{
	if (!CanFire()) return;

	CurrentWeapon->StartFire();
}

void UWeaponComponent::EndFire() {
	if (!CurrentWeapon) return;

	CurrentWeapon->StopFire();
}

void UWeaponComponent::DestroyWeapon()
{
	if (!CurrentWeapon) return;

	//creating for cycle to destroy all weapons
	for (int32 i = 0; i < Weapons.Num(); i++)
	{
		const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) continue;

		FDataOfGame DataOfGame;
		Weapons[i]->SetLifeSpan(DataOfGame.RespawnSeconds);
	}
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void UWeaponComponent::InitAnimations()
{
	auto EquipFinishedNotify = FindNotifyByClass<UEquipAnimNotify>(EquipAnimMontage);
	if(EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);
	}
	
	for(auto MyWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = FindNotifyByClass<UReloadAnimNotify>(MyWeaponData.ReloadAnimations);
		if (!ReloadFinishedNotify) continue;
		{
			ReloadFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnReloadFinished);
		}
	}
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent !=Character->GetMesh()) return;

	//clearing our timer that we created before
	DeAnimation();

	AnimationChange = false;
}

void UWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent !=Character->GetMesh()) return;


	ReloadAnimation = false;
}

bool UWeaponComponent::CanFire()
{
	return CurrentWeapon && !AnimationChange && !ReloadAnimation ;
}

bool UWeaponComponent::CanSwap()
{
	return !AnimationChange && !ReloadAnimation;
}

bool UWeaponComponent::CanReload()
{
	return CurrentWeapon && !AnimationChange && !ReloadAnimation && CurrentWeapon->CanReload();
}

void UWeaponComponent::OnEmptyClip(ARiffleWeapon* AmmoEmpryWeapon)
{
	if (!AmmoEmpryWeapon) return;
	if(CurrentWeapon == AmmoEmpryWeapon)
	{
		ChangeClip();
	}
	else
	{
		for(const auto Weapon: Weapons)
		{
			if(Weapon == AmmoEmpryWeapon)
			{
				ChangeClip();
			}
		}
	}
}

bool UWeaponComponent::NeedAmmo(TSubclassOf<ARiffleWeapon> WeaponType)
{
	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return !Weapon->IsAmmoFull();
		}
	}
	return false;
}

void UWeaponComponent::Zoom(bool Enabled)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Zoom(Enabled);
	}
}

void UWeaponComponent::ChangeClip()
{
	if (!CanReload()) return;

	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	PlayAnimMontage(CurrentReloadAnimMontage);
	ReloadAnimation = true;
	EndFire();
}

void UWeaponComponent::AnimationUI()
{
	IsNextWeapon = true;
}

void UWeaponComponent::DeAnimation()
{
	IsNextWeapon = false;
}


bool UWeaponComponent::GiveAmmo(TSubclassOf<ARiffleWeapon> WeaponType, int32 ClipsAmount)
{
	for(const auto Weapon : Weapons)
	{
		if(Weapon&& Weapon->IsA(WeaponType))
		{
			return Weapon->GiveAmmo(ClipsAmount);
		}
	}
	return false;
}








