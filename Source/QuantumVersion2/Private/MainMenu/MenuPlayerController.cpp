// Quantum.All rights reserved!


#include "MainMenu/MenuPlayerController.h"

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
