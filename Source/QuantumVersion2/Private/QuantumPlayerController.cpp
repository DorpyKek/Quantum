// Quantum.All rights reserved!


#include "QuantumPlayerController.h"
#include "Components/RespawnComponent.h"
#include "QuantumGameModeBase.h"
#include "UI/PauseWidget.h"
#include "Gameframework/GameModeBase.h"

AQuantumPlayerController::AQuantumPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
}



void AQuantumPlayerController::BeginPlay()
{
	if (GetWorld())
	{
		const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AQuantumPlayerController::OnMatchStateChanged);
		}
	}
}

void AQuantumPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	OnNewPawn.Broadcast(NewPawn);
}

void AQuantumPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("Pause", IE_Pressed, this, &AQuantumPlayerController::OnGamePaused);
	
}

void AQuantumPlayerController::OnGamePaused()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
	
}

void AQuantumPlayerController::OnMatchStateChanged(EQuantumMatchState State)
{
	if (State == EQuantumMatchState::Playing)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}



