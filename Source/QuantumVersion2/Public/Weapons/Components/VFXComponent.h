// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VFXComponent.generated.h"


class UNiagaraSystem;
class UPhysicalMaterial;
class USoundCue;


//creating new struct for our decal data
USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "VFX")
	UMaterialInterface* Material;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "VFX")
	FVector Size = FVector(12.0f);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		float LifeSpan = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
		float FadeStartTime = 0.5f;
}
;

//creating another struct of our impact data
USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* NiagaraEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FDecalData DecalData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SFX")
	USoundCue* ImpactSoundCue;
}
;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class QUANTUMVERSION2_API UVFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVFXComponent();

	//creating new function to play our effect while we are shooting 
	void PlayFireFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FImpactData DefaultImpactData;

	//creating new physical material for our effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
