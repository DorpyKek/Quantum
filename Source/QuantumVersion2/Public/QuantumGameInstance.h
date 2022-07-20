// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainMenu/UI/LevelSelectorWidget.h"
#include "QuantumGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UQuantumGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FLevelData GetStartupLevel() const { return StartLevelName; }
	
	void SetStartupLevel(const FLevelData& LevelData) { StartLevelName = LevelData; }

	TArray<FLevelData>GetLevelsData() const { return LevelsData; }
	
	FName GetMainMenuLevel() const { return MenuLevelName; }
protected:
	

	UPROPERTY(EditDefaultsOnly, Category = "Game Instance")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditAnywhere, Category = "Levels")
	TArray<FLevelData>LevelsData;

private:
	UPROPERTY(EditDefaultsOnly,Category = "Game Instance")
	FLevelData StartLevelName;	
};
