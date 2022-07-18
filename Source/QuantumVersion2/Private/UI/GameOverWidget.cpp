// Quantum.All rights reserved!


#include "UI/GameOverWidget.h"
#include "QuantumGameModeBase.h"
#include "UI/PlayerStatisticsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/VerticalBox.h"



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

void UGameOverWidget::RestartGame()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(GetWorld(), FName(CurrentLevelName));
}

void UGameOverWidget::NativeOnInitialized()
{

	Super::NativeOnInitialized();
	
	if(GetWorld())
	{
		const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UGameOverWidget::OnMatchStateChanged);
		}
	}
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::RestartGame);
	}
}
