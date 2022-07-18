// Quantum.All rights reserved!


#include "MainMenu/UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "QuantumGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::StartGame);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
	}
}

void UMainMenuWidget::StartGame()
{
	if (!GetWorld()) return;

	const auto GameInstance = GetWorld()->GetGameInstance<UQuantumGameInstance>();
	if (!GameInstance) return;

	if (GameInstance->GetStartupLevel().IsNone())
	{
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetStartupLevel());
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
