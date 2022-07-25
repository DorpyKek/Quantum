// Quantum.All rights reserved!


#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "QuantumBaseCharacter.h"
#include "GameFramework/Pawn.h"
#include "ComponentGetter.h"
#include "Camera/CameraShakeBase.h"
#include "QuantumGameModeBase.h"
#include "GameFramework/Controller.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Perception/AISense_Damage.h"
DECLARE_LOG_CATEGORY_CLASS(HealthLog, All, All)


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	
}



void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	Health = MaxHealth;

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &UHealthComponent::OnTakePointDamage);
		ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UHealthComponent::OnTakeRadialDamage);
	}
	
}



void UHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	
	
}

void UHealthComponent::Healing()
{
	if (Health < MaxHealth && !IsDead())
	{
		Health = FMath::Clamp(Health + HealCount, 0.0f, MaxHealth);
		OnHealthChanged.Broadcast(Health,0.0f);
	}
	//if our health equals max health we are clearing the timer
	if (Health == MaxHealth)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Heal);
	}
}

void UHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;
	const auto Player = Cast<APawn>(GetOwner());
	
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();

	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UHealthComponent::SetHealth(float NewHealth)
{

	const auto NextHealth = FMath::Clamp(NewHealth,0.0f,MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	Health = NextHealth;
	OnHealthChanged.Broadcast(Health,HealthDelta);
}

void UHealthComponent::Killed(AController* KillerController)
{
	if (!GetWorld()) return;
	const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());

	if (!GameMode) return;

	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);
}

void UHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
	UE_LOG(HealthLog, Display, TEXT("On radial damage: %f, bone: %s"), FinalDamage, *BoneName.ToString());
	ApplyDamage(FinalDamage, InstigatedBy);

}

void UHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	ApplyDamage(Damage, InstigatedBy);
}

void UHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	//clamping our health
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health,Health);


	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Heal, this, &UHealthComponent::Healing,HealRate,true,HealDelay);

	//checking if we are dead  
	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}

	PlayCameraShake();

	ReportDamageEvent(Damage, InstigatedBy);
}

float UHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
	const auto Character = Cast<ACharacter>(DamagedActor);
	if (!Character) return 1.0f;

	if (!Character || !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName)) return 1.0f;

	const auto PhysMat = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
	if (!DamageModifiers.Contains(PhysMat)) return 1.0f;

	return DamageModifiers[PhysMat];
}

void UHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if (!InstigatedBy || !GetWorld() || !InstigatedBy->GetPawn()) return;

	UAISense_Damage::ReportDamageEvent(GetWorld(), GetOwner(), InstigatedBy->GetPawn(), Damage, 
		InstigatedBy->GetPawn()->GetActorLocation(), GetOwner()->GetActorLocation());
}

bool UHealthComponent::HealPlayerFromPick(float HealthAmount)
{
	if (HealthAmount <= 0.0f) return false;
	if (Health >= MaxHealth) return false;
	Health = FMath::Clamp(Health + HealthAmount, 0.0f, MaxHealth);	
	return true;
}








