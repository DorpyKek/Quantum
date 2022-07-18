// Quantum.All rights reserved!


#include "UI/PauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "QuantumPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"


void UPauseWidget::NativeOnInitialized()
{

	Super::NativeOnInitialized();
	const auto Success = Super::Initialize();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::ResumeGame);
	}	
}





void UPauseWidget::ResumeGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}