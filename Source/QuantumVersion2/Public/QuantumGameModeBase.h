// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ComponentGetter.h"
#include "QuantumGameModeBase.generated.h"


class AAIController;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchChangedSignature, EQuantumMatchState)

UENUM(BlueprintType)
enum class EQuantumMatchState : uint8
{
	WaitToStart = 0,
	Playing,
	Pause,
	GameOver
};

USTRUCT(BlueprintType)
struct FDataOfGame
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
	int32 PlayersNum = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
	int32 RoundsNum = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "300"))
	int32 Seconds; //all in seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "0", ClampMax = "5"))
	int32 Minutes; //all in minutes

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor DefaultColor = FLinearColor::Red;   //this color is goint to be set if our bp hasnt been set

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLinearColor> TeamColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "15"))
	int32 RespawnSeconds = 3;
	
};
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API AQuantumGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AQuantumGameModeBase();

	FOnMatchChangedSignature OnMatchStateChanged;

	virtual void StartPlay() override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void Killed(AController* KillerController, AController* VictimController);

	int32 CurrenRound = 1;
	int32 MinutesCountDown = 0;
	int32 SecondsCountDown = 0;
	FTimerHandle SecondsTimerHandle;
	FTimerHandle MinutesTimerHandle;

	void RespawnRequest(AController* Controller);

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	virtual bool ClearPause() override;

	int32 RoundsLeft();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FDataOfGame DataOfGame;


private:
	EQuantumMatchState MatchState = EQuantumMatchState::WaitToStart;
	
	void BotSpawn();
	void RoundStart();
	void TimerUpdate();
	

	void RespawnPlayers();
	void ResetOnePlayer(AController* Controller);

	void CreateTeamInfo();
	FLinearColor DetermineColorById(int32 TeamId) const;
	void SetColorOfPlayer(AController* Controller);

	void LogPlayerInfo();

	void StartRespawn(AController* Controller);

	void GameOver();

	

	void SetMatchState(EQuantumMatchState State);

	
	
};
