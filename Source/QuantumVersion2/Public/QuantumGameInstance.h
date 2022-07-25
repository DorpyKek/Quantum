// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainMenu/UI/LevelSelectorWidget.h"
#include "QuantumGameInstance.generated.h"

class USoundClass;
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

	void ToggleVolume();
protected:
	

	UPROPERTY(EditDefaultsOnly, Category = "Game Instance")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditAnywhere, Category = "Levels")
	TArray<FLevelData>LevelsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundClass* MasterSoundClass;

private:
	UPROPERTY(EditDefaultsOnly,Category = "Game Instance")
	FLevelData StartLevelName;	
};
