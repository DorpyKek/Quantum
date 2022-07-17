// Quantum.All rights reserved!


#include "AI/Decorators/HealthDecorator.h"
#include "AIController.h"
#include "ComponentGetter.h"
#include "Components/HealthComponent.h"

UHealthDecorator::UHealthDecorator()
{
	NodeName = "Health Percentage";
}

bool UHealthDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;
	
	const auto HealthComponent = UComponentGetter::GetPlayerComponent<UHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
