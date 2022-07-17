// Quantum.All rights reserved!


#include "UI/MarkerWidget.h"
#include "Weapons/M16Weapon.h"
#include "Kismet/GameplayStatics.h"

bool UMarkerWidget::IsHitted()
{
	//getting our weapon and checking if our trace after fire hit actor than we are returning true
	AM16Weapon* Weapon = Cast<AM16Weapon>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	if (!Weapon) return false;

	const auto HittedResult = Weapon->Hitted;

	return HittedResult;
}
