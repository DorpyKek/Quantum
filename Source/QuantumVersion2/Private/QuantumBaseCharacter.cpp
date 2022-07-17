// Quantum.All rights reserved!


#include "QuantumBaseCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Weapons/RiffleWeapon.h"
#include "Weapon/WeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraShakeBase.h"
#include "UI/PlayerHUDWidget.h"
#include "GameFramework/Controller.h"


DECLARE_LOG_CATEGORY_CLASS(CharacterLog, All, All);

// Sets default values
AQuantumBaseCharacter::AQuantumBaseCharacter(const FObjectInitializer& ObjInit)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//creating here component which is goint to be responsible for health of our player;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void AQuantumBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth(),0.0f);

	bool CanJump = true;

	HealthComponent->OnDeath.AddUObject(this, &AQuantumBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AQuantumBaseCharacter::OnHealthChanged);
	}

void AQuantumBaseCharacter::OnHealthChanged(float Health,float DeltaHealth)
{
	
}

void AQuantumBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
	
	if (FallVelocityZ < LandedDamageVelocity.X)
	{
		return;
	}
	
	//applying our fall damage to player
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
	
}

// Called every frame
void AQuantumBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AQuantumBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInstance) return;

	MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}



void AQuantumBaseCharacter::OnDeath()
{
	UE_LOG(CharacterLog, Error, TEXT("Player is dead!"));
	//PlayAnimMontage(DeathAnimationMontage);

	//disabling our character`s movement when we are dead and deleting actor in some time;
	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//stopping the fire when we are dead
	WeaponComponent->EndFire();

	//whene we are dead destroying weapon
	WeaponComponent->DestroyWeapon();

	//setting our character to ragdoll
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	
}













