// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "QuantumGameSetting.generated.h"

USTRUCT()
struct FSettingOption
{
	GENERATED_BODY();

	FString Name;

	int32 Value;
	
};

UCLASS()
class UQuantumGameSetting : public UObject {
	
	GENERATED_BODY()

public:
	void SetName(const FString& Name);
	
	void SetOptions(const TArray<FSettingOption>& Options);

	FSettingOption GetCurrentOption() const;
	FString GetName() const;
	void AddGeter(TFunction<int32()> Func);
	void AddSetter(TFunction<void(int32)> Func);

	void ApplyNextOption();
	void ApplyPrevOption();

private:
	FString Name;
	TArray<FSettingOption> Options;
	TFunction<int32()>Getter;
	TFunction<void(int32)>Setter;

	void SetCurrentValue(int32 Value);

	int32 GetCurrentIndex() const;

	int32 GetCurrentValue() const;
};
