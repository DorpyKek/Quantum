// Quantum.All rights reserved!


#include "UI/SettingsSelectroUserWidget.h"
#include "QuantumGameModeBase.h"
#include "Components/Button.h"
#include "UI/PauseWidget.h"


void USettingsSelectroUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	check(VideoSettingsButton);
	check(AudioSettingsButton);
	check(BackToPauseButton);

	VideoSettingsButton->OnClicked.AddDynamic(this, &USettingsSelectroUserWidget::OnVideoSettingsButtonClicked);
	AudioSettingsButton->OnClicked.AddDynamic(this, &USettingsSelectroUserWidget::OnAudioSettingsButtonClicked);
	BackToPauseButton->OnClicked.AddDynamic(this, &USettingsSelectroUserWidget::OnBackToPauseButtonClicked);
}

void USettingsSelectroUserWidget::OnVideoSettingsButtonClicked()
{
	const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	
	GameMode->SetMatchState(EQuantumMatchState::VideoSetting);
}

void USettingsSelectroUserWidget::OnAudioSettingsButtonClicked()
{
	const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->SetMatchState(EQuantumMatchState::SoundSetting);
}

void USettingsSelectroUserWidget::OnBackToPauseButtonClicked()
{
	const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	

	GameMode->SetMatchState(EQuantumMatchState::Pause);
}
