// Quantum.All rights reserved!


#include "AI/AIBaseController.h"
#include "Components/CharacterAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/RespawnComponent.h"
#include "AI/AIBaseCharacter.h"



AAIBaseController::AAIBaseController()
{
	CharacterPercreptionComponent = CreateDefaultSubobject<UCharacterAIPerceptionComponent>("CharacterPercreptionComponent");
	SetPerceptionComponent(*CharacterPercreptionComponent);

	RespawnComponent = CreateDefaultSubobject<URespawnComponent>("RespawnComponent");

	bWantsPlayerState = true;
}

void AAIBaseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AAIBaseCharacter>(InPawn);

	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTree);
	}
}

void AAIBaseController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusedActor();
	SetFocus(AimActor);
}
 
AActor* AAIBaseController::GetFocusedActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusKeyName));
	
}


