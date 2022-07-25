// Quantum.All rights reserved!


#include "Components/CharacterAIPerceptionComponent.h"
#include "AIController.h"
#include "ComponentGetter.h"
#include "Components/HealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"

AActor* UCharacterAIPerceptionComponent::GetClosestEnemy() const
{
	//creating massive to contain all characters that has been seen by ai
	TArray<AActor*> PerceiveCharacters;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveCharacters);
	if (PerceiveCharacters.Num() == 0)
	{
		GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PerceiveCharacters);
		if (PerceiveCharacters.Num() == 0) return nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;
	
	float ClosestDistance = MAX_FLT;
	AActor* ClosestCharacter = nullptr;
	
	//calculating the distance between the characters and the ai
	for (const auto PercieveActor : PerceiveCharacters)
	{
		const auto HealthComponent = PercieveActor->FindComponentByClass<UHealthComponent>();

		const auto PerceivePawn = Cast<APawn>(PercieveActor);
		const auto AreEnemies = PerceivePawn && UComponentGetter::AreEnemies(Controller, PerceivePawn->Controller);

		if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < ClosestDistance)
			{
				ClosestDistance = CurrentDistance;
				ClosestCharacter = PercieveActor;
			}
		}
	}

	return ClosestCharacter;
}
