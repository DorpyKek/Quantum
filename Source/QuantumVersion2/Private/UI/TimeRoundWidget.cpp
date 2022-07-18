// Quantum.All rights reserved!


#include "UI/TimeRoundWidget.h"
#include "ComponentGetter.h"
#include "Kismet/GameplayStatics.h"
#include "GameCore/QuantumPlayerState.h"

int32 UTimeRoundWidget::GetCurrentTimeInSeconds() const
{
	const auto GameMode = Cast<AQuantumGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return 0;

	const auto Seconds = GameMode->SecondsCountDown;

	return Seconds;
}

int32 UTimeRoundWidget::GetCurrentTimeInMinutes() const
{

	const auto GameMode = Cast<AQuantumGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return 0;

	const auto Minutes = GameMode->MinutesCountDown;
	
	return Minutes;
}

int32 UTimeRoundWidget::GetCurrentRound() const
{
	const auto GameMode = Cast<AQuantumGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return 0;

	return GameMode->CurrenRound;
}

int32 UTimeRoundWidget::GetRoundsNum() const 
{
	const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return 0;

	return GameMode->RoundsLeft();
}

bool UTimeRoundWidget::IsTimeLess10() const
{
	const auto GameMode = Cast<AQuantumGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return false;

	if (GameMode->SecondsCountDown < 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UTimeRoundWidget::IsFewSeconds() const
{
	const auto GameMode = Cast<AQuantumGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return false;

	if (GameMode->MinutesCountDown == 0 && GameMode->SecondsCountDown <= 30)
	{
		return true;
	}
	else
	{
		return false;
	}
}
