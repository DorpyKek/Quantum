// Quantum.All rights reserved!


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Weapon/WeaponComponent.h"


APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject <UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(30.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void APlayerCharacter::OnDeath()
{
	
	Super::OnDeath();
	//when we are dead our controller going into spectating mode 
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnCameraBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnCameraEndOverlap);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//using input component in header file to connect mapping axes and functions below;

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::OnSprintStart);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::OnSprintEnd);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UWeaponComponent::EndFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);
	
}

void APlayerCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void APlayerCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void APlayerCharacter::OnSprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
}

void APlayerCharacter::OnSprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void APlayerCharacter::OnCameraBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void APlayerCharacter::OnCameraEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}

void APlayerCharacter::CheckCameraOverlap()
{
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	if (!HideMesh) return;

	GetMesh()->SetOwnerNoSee(HideMesh);
}


