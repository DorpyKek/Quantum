// Quantum.All rights reserved!


#include "AI/AIBaseCharacter.h"
#include "AI/AIBaseController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/AIWeaponComponent.h"
#include "BrainComponent.h"
#include "ComponentGetter.h"

AAIBaseCharacter::AAIBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AAIBaseController::StaticClass();
	
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
