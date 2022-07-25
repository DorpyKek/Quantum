// Quantum.All rights reserved!


#include "Weapons/Components/VFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Math/Vector.h"
#include "Sound/SoundCue.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

UVFXComponent::UVFXComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

}

void UVFXComponent::PlayFireFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;
	
	//changing our effect depens on where our hit was shot
	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}
	
	//spawning the niagara effect
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactData.ImpactSoundCue, Hit.ImpactPoint);


	//spawning the decal

	//creating new variable which is going to contain rotation from x vector from impact normal
	FRotator DecalRotation = Hit.ImpactNormal.Rotation();
	
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), 
		ImpactData.DecalData.Material, 
		ImpactData.DecalData.Size, 
		Hit.ImpactPoint, 
		DecalRotation);

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeSpan, 
			ImpactData.DecalData.FadeStartTime);
	}
}




