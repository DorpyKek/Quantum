// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "QuantumGameUserSettings.generated.h"

class UQuantumGameSetting;

DECLARE_MULTICAST_DELEGATE(FOnSettingsUpdateDelegate);

UCLASS()
class QUANTUMVERSION2_API UQuantumGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UQuantumGameUserSettings();
	static UQuantumGameUserSettings* Get();

	const TArray<UQuantumGameSetting*>& GetVideoSettings() const;

	void SetAutoSettings();
	
	FOnSettingsUpdateDelegate OnVideoSettingsUpdate;

private:
	UPROPERTY()
	TArray<UQuantumGameSetting*>VideoSettings;																	
	
};
