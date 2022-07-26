// Quantum.All rights reserved!


#include "UI/Settings/GameUserSettings/QuantumGameUserSettings.h"
#include "UI/Settings/GameUserSettings/QuantumGameSetting.h"


UQuantumGameUserSettings::UQuantumGameUserSettings()
{
	TArray<FSettingOption> VFXOptions = { {"Low", 0}, {"Medium", 1}, {"High", 2}, {"Epic", 3} }; 
	{
		auto* Settings = NewObject<UQuantumGameSetting>();
		check(Settings);
		Settings->SetName("Anti-Aliasing");
		Settings->SetOptions(VFXOptions);
		Settings->AddGeter([&]() { return GetAntiAliasingQuality(); });
		Settings->AddSetter([&](int32 LevelOfQuality) { SetAntiAliasingQuality(LevelOfQuality); ApplySettings(false); });
		VideoSettings.Add(Settings);
	}

	{
		auto* Settings = NewObject<UQuantumGameSetting>();
		check(Settings);
		Settings->SetName("Texture Quality");
		Settings->SetOptions(VFXOptions);
		Settings->AddGeter([&]() { return GetTextureQuality(); });	
		Settings->AddSetter([&](int32 LevelOfQuality) { SetTextureQuality(LevelOfQuality); ApplySettings(false); });
		VideoSettings.Add(Settings);
	}
	
	{
		auto* Settings = NewObject<UQuantumGameSetting>();
		check(Settings);
		Settings->SetName("Global Illumination");
		Settings->SetOptions(VFXOptions);
		Settings->AddGeter([&]() { return GetGlobalIlluminationQuality(); });
		Settings->AddSetter([&](int32 LevelOfQuality) { SetGlobalIlluminationQuality(LevelOfQuality); ApplySettings(false); });
		VideoSettings.Add(Settings);
	}
	
	{
		auto* Settings = NewObject<UQuantumGameSetting>();
		check(Settings);
		Settings->SetName("Shadow Quality");
		Settings->SetOptions(VFXOptions);
		Settings->AddGeter([&]() { return GetShadowQuality(); });
		Settings->AddSetter([&](int32 LevelOfQuality) { SetShadowQuality(LevelOfQuality); ApplySettings(false); });
		VideoSettings.Add(Settings);
	}
	
	{
		auto* Settings = NewObject<UQuantumGameSetting>();
		check(Settings);
		Settings->SetName("Post Proccesing");
		Settings->SetOptions(VFXOptions);
		Settings->AddGeter([&]() { return GetPostProcessingQuality(); });
		Settings->AddSetter([&](int32 LevelOfQuality) { SetPostProcessingQuality(LevelOfQuality); ApplySettings(false); });
		VideoSettings.Add(Settings);
	}

	{
		auto* Settings = NewObject<UQuantumGameSetting>();
		check(Settings);
		Settings->SetName("View Distance");
		Settings->SetOptions(VFXOptions);
		Settings->AddGeter([&]() { return GetViewDistanceQuality(); });
		Settings->AddSetter([&](int32 LevelOfQuality) { SetViewDistanceQuality(LevelOfQuality); ApplySettings(false); });
		VideoSettings.Add(Settings);
	}

	{
		auto* Settings = NewObject<UQuantumGameSetting>();
		check(Settings);
		Settings->SetName("Effects");
		Settings->SetOptions(VFXOptions);
		Settings->AddGeter([&]() { return GetVisualEffectQuality(); });
		Settings->AddSetter([&](int32 LevelOfQuality) { SetVisualEffectQuality(LevelOfQuality); ApplySettings(false); });
		VideoSettings.Add(Settings);
		
	}
	
}

UQuantumGameUserSettings* UQuantumGameUserSettings::Get()
{
	return GEngine ? Cast<UQuantumGameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

const TArray<UQuantumGameSetting*>& UQuantumGameUserSettings::GetVideoSettings() const
{
	return VideoSettings;
}

void UQuantumGameUserSettings::SetAutoSettings()
{
	RunHardwareBenchmark();
	ApplySettings(false);
	OnVideoSettingsUpdate.Broadcast();
}
