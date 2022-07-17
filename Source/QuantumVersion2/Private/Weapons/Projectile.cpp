// Quantum.All rights reserved!


#include "Weapons/Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/LauncherWeapon.h"
#include "Weapons/Components/VFXComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	WeaponVFXComponent = CreateDefaultSubobject<UVFXComponent>("WeaponFXComponent");
	
}



void AProjectile::BeginPlay()
{	
	Super::BeginPlay();

	check(ProjectileMovementComponent);
	check(CollisionComponent);
	check(WeaponVFXComponent);

	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
	SetLifeSpan(LifeSeconds);
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;
	
	ProjectileMovementComponent->StopMovementImmediately();

	//setting radial damage
	UGameplayStatics::ApplyRadialDamage(GetWorld(),
		ProjectileDamage,
		GetActorLocation(),
		DamageRadius,
		UDamageType::StaticClass(),
		{ GetOwner() },
		this,
		GetController(),
		DoFullDamage);

	
	WeaponVFXComponent->PlayFireFX(Hit);

	Destroy();
}

AController* AProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
	
	
	
}



