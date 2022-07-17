// Quantum.All rights reserved!


#include "AI/Tasks/NextLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UNextLocation::UNextLocation()
{
	NodeName = "Find Next Location";
}

EBTNodeResult::Type UNextLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//creating owner of ai controller and getting blackboard component
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	
	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	//getting pawn pointer 
	const auto Pawn = Controller->GetPawn();

	if (!Pawn) return EBTNodeResult::Failed;
	
	const auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavSystem) return EBTNodeResult::Failed;

	
	//getting random location using radius 
	FNavLocation NavLocation;
	auto Location = Pawn->GetActorLocation();

	if (!SelfCenter)
	{
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if(!CenterActor) return EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();
	}

	const auto Found = NavSystem->GetRandomPointInNavigableRadius(Location, Radius,NavLocation);

	if (!Found) return EBTNodeResult::Failed;

	//setting location to blackboard
	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
	
}
