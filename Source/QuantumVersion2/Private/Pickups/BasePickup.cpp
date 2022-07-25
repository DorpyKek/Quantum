// Quantum.All rights reserved!


#include "Pickups/BasePickup.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/SphereComponent.h"


DEFINE_LOG_CATEGORY_STATIC(PickupLog, All, All);

ABasePickup::ABasePickup()
{
	//creating new collision for our pickups
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionComponent->InitSphereRadius(50.0f);
	SetRootComponent(CollisionComponent);

	PrimaryActorTick.bCanEverTick = true;
}

bool ABasePickup::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimer);
}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);

	GenerateRotation();
	
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (!Pawn) return;
	
	if (GetPickupInfo(Pawn))
	{
		PickupTook();
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PickUpSoundCue, GetActorLocation());
	}
	
	
}

bool ABasePickup::GetPickupInfo(APawn* PlayerPawn)
{
	return false;
}

void ABasePickup::PickupTook()
{
	//disabling all collision 
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	//making our object invisible
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}

	//creating timer for respawn 
	
	GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &ABasePickup::Respawn, TimeForRespawn);
}

void ABasePickup::Respawn()
{
	//enabling our collision
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
	GenerateRotation();
}

void ABasePickup::GenerateRotation()
{
	//generating random rotation for our pickups
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::FRandRange(1.0f, 2.0f) * Direction;
}


