// Quantum.All rights reserved!


#include "UI/GameOverWidget.h"
#include "QuantumGameModeBase.h"
#include "UI/PlayerStatisticsWidget.h"
#include "Components/VerticalBox.h"

bool UGameOverWidget::Initialize()
{
	if(GetWorld())
	{
		const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UGameOverWidget::OnMatchStateChanged);
		}
	}
    return Super::Initialize();
}

void UGameOverWidget::OnMatchStateChanged(EQuantumMatchState State)
{
	if (State == EQuantumMatchState::GameOver)
	{
		UpdatePlayerStatistics();
	}
}

void UGameOverWidget::UpdatePlayerStatistics()
{
	if (!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for(auto It =GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;
		
		const auto PlayerState = Cast<AQuantumPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		const auto PlayerStaticsRowWidget = CreateWidget<UPlayerStatisticsWidget>(GetWorld(), PlayerStatisticsRowWidget);
		if (!PlayerStaticsRowWidget) continue;

		PlayerStaticsRowWidget->SetNameText(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStaticsRowWidget->SetKillsText(FText::FromString(FString::FromInt(PlayerState->GetKills())));
		PlayerStaticsRowWidget->SetDeathsText(FText::FromString(FString::FromInt(PlayerState->GetDeaths())));
		PlayerStaticsRowWidget->SetTeamNumberText(FText::FromString(FString::FromInt(PlayerState->GetTeamId())));
		PlayerStaticsRowWidget->SetPlayerImageVisibility(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStaticsRowWidget);
	}
}
