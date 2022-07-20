// Quantum.All rights reserved!


#include "UI/HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHealthPercent(float Health)
{
	if (!HealthProgressBar) return;
	
	const auto HealthBarVisibility = (Health > PercentageVisibility || FMath::IsNearlyZero(Health)) 
		? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	HealthProgressBar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = Health > LowPercentageColor ? HealthColor : LowHealthColor;
	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressBar->SetPercent(Health);
}
