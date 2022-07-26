// Quantum.All rights reserved!


#include "UI/PauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "QuantumGameModeBase.h"
#include "QuantumPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "QuantumGameInstance.h"
#include "Components/Button.h"


void UPauseWidget::NativeOnInitialized()
{

	Super::NativeOnInitialized();
	const auto Success = Super::Initialize();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::ResumeGame);
	}

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UPauseWidget::ReturnToMainMenu);
	}

	check(SettingsButton);

	SettingsButton->OnClicked.AddDynamic(this, &UPauseWidget::OpenSettings);
}





void UPauseWidget::ResumeGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();

	ResumeButton->SetVisibility(ESlateVisibility::Hidden);
	MainMenuButton->SetVisibility(ESlateVisibility::Hidden);
}

void UPauseWidget::ReturnToMainMenu()
{
	if (!GetWorld()) return;
	
	const auto GameInstance = GetWorld()->GetGameInstance<UQuantumGameInstance>();
	if (!GameInstance) return;

	const auto LevelName = GameInstance->GetMainMenuLevel();

	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void UPauseWidget::OpenSettings()
{
	const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());

	GameMode->SetMatchState(EQuantumMatchState::Setting);

	ResumeButton->SetVisibility(ESlateVisibility::Hidden);
	MainMenuButton->SetVisibility(ESlateVisibility::Hidden); 
}
