// Quantum.All rights reserved!


#include "AI/AIBaseCharacter.h"
#include "AI/AIBaseController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/AIWeaponComponent.h"
#include "BrainComponent.h"
#include "ComponentGetter.h"
#include "Weapon/WeaponComponent.h"
#include "UI/HealthBarWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/HealthComponent.h"

AAIBaseCharacter::AAIBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AAIBaseController::StaticClass();

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
	
	
	bUseControllerRotationYaw = false;
	
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void AAIBaseCharacter::OnDeath()
{
	//stopping our behavior tree
	Super::OnDeath();

	const auto PlayerController = Cast<AAIController>(Controller);
	if(PlayerController && PlayerController->BrainComponent)
	{
		PlayerController->BrainComponent->Cleanup();
	}

	
}

void AAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthWidgetComponent);
}

void AAIBaseCharacter::OnHealthChanged(float Health, float DeltaHealth)
{
	Super::OnHealthChanged(Health, DeltaHealth);

	const auto HealthWidget = Cast<UHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	HealthWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHeatlhWidgetVisibility();
}

void AAIBaseCharacter::UpdateHeatlhWidgetVisibility()
{
	if (!GetWorld() || !GetWorld()->GetFirstPlayerController()) return;

	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
	HealthWidgetComponent->SetVisibility(Distance < HealtVisibilityPercentageDistance, true);
}


