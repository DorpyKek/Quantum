// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/RiffleWeapon.h"
#include "WeaponComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmpty, ARiffleWeapon*);


class ARiffleWeapon;
class UAnimMontage;



USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ARiffleWeapon>WeaponClass;

	//creating another struct of our weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		UAnimMontage* ReloadAnimations;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUANTUMVERSION2_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UWeaponComponent();

	virtual void StartFire();
	void EndFire();

	void DestroyWeapon();

	virtual void NextWeapon();	

	void Reload();
	
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
	
	bool IsNextWeapon;

	bool GiveAmmo(TSubclassOf<ARiffleWeapon> WeaponType, int32 ClipsAmount);

	void OnEmptyClip(ARiffleWeapon* AmmoEmpryWeapon);

	UPROPERTY()
	ARiffleWeapon* CurrentWeapon = nullptr;

	bool NeedAmmo(TSubclassOf<ARiffleWeapon> WeaponType);
	
	void Zoom(bool Enabled);

	
	
protected:
	
	UPROPERTY(EditDefaultsOnly,Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponPoint";
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	//creating anim montage 
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;

	

	

	//creating array with weapons to contain our weapon index
	UPROPERTY()
	TArray<ARiffleWeapon*> Weapons;

	bool CanFire() ;
	bool CanSwap();

	void EquipWeapon(int32 WeaponIndex);
	
	int32 CurrentWeaponIndex = 0;


private:

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	//creating bool to control animation
	bool AnimationChange = false;
	bool ReloadAnimation = false;

		
	void SpawnWeapons();
	void AttachWeaponToSocket(ARiffleWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanReload();

	
	void ChangeClip();

	void AnimationUI();
	void DeAnimation();

	//creating template 
	template<typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{

		const auto NotifyEvents = Animation->Notifies;

		for(auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);
			if(AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}

	
};