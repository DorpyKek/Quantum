// Quantum.All rights reserved!


#include "UI/Settings/GameUserSettings/QuantumGameSetting.h"

DEFINE_LOG_CATEGORY_STATIC(LogOfSettings, All, All);

void UQuantumGameSetting::SetName(const FString& InName)
{
    Name = InName;
}

void UQuantumGameSetting::SetOptions(const TArray<FSettingOption>& InOptions)
{
    Options = InOptions;
}

FSettingOption UQuantumGameSetting::GetCurrentOption() const
{
    const int32 CurrentValue = GetCurrentValue();
    
    const auto Option = Options.FindByPredicate([&](const auto& Opt) { return CurrentValue == Opt.Value; });

    if (!Option)
    {
        UE_LOG(LogOfSettings, Error, TEXT("Option doesn`t exist "));
        return FSettingOption{};
    }

    return *Option;
}

FString UQuantumGameSetting::GetName() const
{
    return Name;
}

void UQuantumGameSetting::AddGeter(TFunction<int32()> Func)
{
    Getter = Func;
}

void UQuantumGameSetting::AddSetter(TFunction<void(int32)> Func)
{
    Setter = Func;
}

void UQuantumGameSetting::ApplyNextOption()
{
    const int32 CurrentIndex = GetCurrentIndex();
    if (CurrentIndex == INDEX_NONE) return;
	
	const int32 NextIndex = (CurrentIndex + 1) % Options.Num();
    SetCurrentValue(Options[NextIndex].Value);
}

void UQuantumGameSetting::ApplyPrevOption()
{
    const int32 CurrentIndex = GetCurrentIndex();
    if (CurrentIndex == INDEX_NONE) return;

	const int32 PrevIndex = CurrentIndex == 0 ? Options.Num() - 1 : CurrentIndex - 1;
	SetCurrentValue(Options[PrevIndex].Value);
}

void UQuantumGameSetting::SetCurrentValue(int32 Value)
{
    if (!Setter)    
    {
        UE_LOG(LogOfSettings, Error, TEXT("Getter doesnt exist for : %s"),*Name);
        return;
    }
    return Setter(Value);
}

int32 UQuantumGameSetting::GetCurrentIndex() const
{
	const int32 CurrentValue = GetCurrentValue();
	
    return Options.IndexOfByPredicate([&](const auto& Opt) {return CurrentValue == Opt.Value; });
}

int32 UQuantumGameSetting::GetCurrentValue() const
{
    if (!Getter)    
    {
		UE_LOG(LogOfSettings, Error, TEXT("Getter doesnt exist for : %s"),*Name);
        return INDEX_NONE;
    }
    return Getter();
}


