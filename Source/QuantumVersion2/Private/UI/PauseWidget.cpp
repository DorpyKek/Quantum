// Quantum.All rights reserved!


#include "UI/PauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "QuantumPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"


bool UPauseWidget::Initialize()
{
	const auto Success = Super::Initialize();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::ResumeGame);
	}

	return Success;
}





void UPauseWidget::ResumeGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}