// Quantum.All rights reserved!


#include "UI/PauseWidget.h"
#include "Gameframework/GameModeBase.h"
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
}





void UPauseWidget::ResumeGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}

void UPauseWidget::ReturnToMainMenu()
{
	if (!GetWorld()) return;
	
	const auto GameInstance = GetWorld()->GetGameInstance<UQuantumGameInstance>();
	if (!GameInstance) return;

	const auto LevelName = GameInstance->GetMainMenuLevel();

	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}
