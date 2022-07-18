// Quantum.All rights reserved!


#include "MainMenu/UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::StartGame);
	}
}

void UMainMenuWidget::StartGame()
{
	const FName StartupLevel = "TestingLevel";
	UGameplayStatics::OpenLevel(GetWorld(), StartupLevel);
}
