// Quantum.All rights reserved!


#include "QuantumGameModeBase.h"
#include "QuantumBaseCharacter.h"
#include "QuantumPlayerController.h"
#include "AI/AIBaseController.h"
#include "UI/GameHUD.h"
#include "GameCore/QuantumPlayerState.h"
#include "ComponentGetter.h"
#include "Components/RespawnComponent.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(GameModeLog, All, All);

AQuantumGameModeBase::AQuantumGameModeBase()
{
	//making our playercontroller and pawn by default
	DefaultPawnClass = AQuantumBaseCharacter::StaticClass();
	PlayerControllerClass = AQuantumPlayerController::StaticClass();
	HUDClass = AGameHUD::StaticClass();
	PlayerStateClass = AQuantumPlayerState::StaticClass();
}

void AQuantumGameModeBase::StartPlay()
{
	Super::StartPlay();

	BotSpawn();

	CurrenRound = 1;
	RoundStart();

	SetMatchState(EQuantumMatchState::Playing);
	
}

UClass* AQuantumGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if(InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	else
	{
		return Super::GetDefaultPawnClassForController_Implementation(InController);
	}
}

void AQuantumGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<AQuantumPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<AQuantumPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}
	
	StartRespawn(VictimController);

}

void AQuantumGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

bool AQuantumGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto Pause = Super::SetPause(PC, CanUnpauseDelegate);
	if (Pause)
	{
		SetMatchState(EQuantumMatchState::Pause);
	}
	return Pause;
}

bool AQuantumGameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	
	if (PauseCleared)
	{
		SetMatchState(EQuantumMatchState::Playing);
	}

	return PauseCleared;
}


void AQuantumGameModeBase::BotSpawn()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < DataOfGame.PlayersNum; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(AIController);
	}
}

void AQuantumGameModeBase::RoundStart()						 
{
	MinutesCountDown = DataOfGame.Minutes;
	SecondsCountDown = DataOfGame.Seconds;
	CreateTeamInfo();
	GetWorldTimerManager().SetTimer(SecondsTimerHandle, this, &AQuantumGameModeBase::TimerUpdate, 1.0f, true);
	GetWorldTimerManager().SetTimer(MinutesTimerHandle, this, &AQuantumGameModeBase::TimerUpdate, 60.0f, true);

}

void AQuantumGameModeBase::TimerUpdate()
{
	UE_LOG(GameModeLog, Error, TEXT("Time left: %i:%i / Round: %i/%i "),MinutesCountDown,SecondsCountDown,CurrenRound,DataOfGame.RoundsNum);
	
	if (MinutesCountDown == 0 && SecondsCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(SecondsTimerHandle);
		GetWorldTimerManager().ClearTimer(MinutesTimerHandle);
		if (CurrenRound + 1 <= DataOfGame.RoundsNum)
		{
			CurrenRound++;
			RespawnPlayers();
			RoundStart();
		}
		else
		{
			GameOver();
		}
	}
	else
	{
		if (SecondsCountDown == 0)
		{
			MinutesCountDown--;
			SecondsCountDown = 59;
		}
		else
		{
			SecondsCountDown--;
		}
	}
}




void AQuantumGameModeBase::RespawnPlayers()
{
	if (!GetWorld()) return;

	for(auto It = GetWorld()->GetControllerIterator();It;++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void AQuantumGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}

	RestartPlayer(Controller);
	SetColorOfPlayer(Controller);	
	
	
}

void AQuantumGameModeBase::CreateTeamInfo()
{
	int32 TeamID = 1;
	for(auto It = GetWorld()->GetControllerIterator();It;++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AQuantumPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamId(TeamID);
		PlayerState->SetColorOfTeam(DetermineColorById(TeamID));
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
		SetColorOfPlayer(Controller);
		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor AQuantumGameModeBase::DetermineColorById(int32 TeamId) const
{
	if (TeamId - 1 < DataOfGame.TeamColors.Num())
	{
		return DataOfGame.TeamColors[TeamId - 1];
	}
	else
	{
		return DataOfGame.DefaultColor;
	}
}

void AQuantumGameModeBase::SetColorOfPlayer(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<AQuantumBaseCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<AQuantumPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetColorOfTeam());

}

void AQuantumGameModeBase::LogPlayerInfo()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AQuantumPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;
		PlayerState->LogInfo();
	}
}

void AQuantumGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnComponent = UComponentGetter::GetPlayerComponent<URespawnComponent>(Controller);
	if (!RespawnComponent) return;

	RespawnComponent->Respawn(DataOfGame.RespawnSeconds);
}

void AQuantumGameModeBase::GameOver()
{
	UE_LOG(GameModeLog, Error, TEXT("======= GAME IS OVER ======="));
	LogPlayerInfo();

	for(auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}
	SetMatchState(EQuantumMatchState::GameOver);
}

void AQuantumGameModeBase::SetMatchState(EQuantumMatchState State)
{
	if (MatchState == State) return;
	
	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}

int32 AQuantumGameModeBase::RoundsLeft()
{
	return DataOfGame.RoundsNum;
}



