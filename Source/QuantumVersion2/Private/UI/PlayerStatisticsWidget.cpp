// Quantum.All rights reserved!


#include "UI/PlayerStatisticsWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UPlayerStatisticsWidget::SetNameText(const FText& Text)
{
	if (!PlayerNameBlock) return;
	PlayerNameBlock->SetText(Text);
}

void UPlayerStatisticsWidget::SetKillsText(const FText& Text)
{
	if (!KillsBlock) return;
	KillsBlock->SetText(Text);
}

void UPlayerStatisticsWidget::SetDeathsText(const FText& Text)
{
	if (!DeathsBlock) return;
	DeathsBlock->SetText(Text);
}

void UPlayerStatisticsWidget::SetTeamNumberText(const FText& Text)
{
	if (!TeamNumberBlock) return;
	TeamNumberBlock->SetText(Text);
}

void UPlayerStatisticsWidget::SetPlayerImageVisibility(bool Visible)
{
	if (!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
