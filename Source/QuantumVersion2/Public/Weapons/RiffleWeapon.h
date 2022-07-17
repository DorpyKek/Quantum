// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RiffleWeapon.generated.h"


class UNiagaraSystem;
class UNiagaraComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmpty, ARiffleWeapon*);

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UTexture2D* MainIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UTexture2D* CrossIcon;

};


USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	//creating property for our ammo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 Bullets;

	//creating leaps
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 Clips;

	//creating bool for infinite
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	bool Infinite;
};


UCLASS()
class QUANTUMVERSION2_API ARiffleWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	// Sets default values for this actor's properties
	ARiffleWeapon();

	FOnClipEmpty OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();

	virtual void Shoot();

	void ChangeClip();
	bool CanReload();

	FWeaponUIData GetUIData() const { return UIData; }

	FAmmoData GetAmmoData() const { return CurrentAmmo; }

	bool GiveAmmo(int32 ClipsAmount);
	bool IsAmmoEmpty() const;

	FVector GetMuzzleWorldLocation() const;

	FAmmoData CurrentAmmo;

	bool IsAmmoFull() const ;

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//creatin uproperty which is going to allow us to modify our weapon in blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	//creating our socket name 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	//creating default ammo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo{20,15,false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFX;
	
	//creating our muzzle flash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float MaxShootDistance = 1500.0f;

	//creating damage 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage = 10.0f;

	void DecreaseAmmo();
	bool IsAmmoClipEmpty() const;
	void LogAmmo();

	UNiagaraComponent* SpawnFX();

	

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

private:
	
	

};
