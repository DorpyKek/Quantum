// Quantum.All rights reserved!


#include "UI/Settings/VideoSettingsWidget.h"
#include "Components/VerticalBox.h"
#include "UI/Settings/SettingsOptionWidget.h"
#include "Components/Button.h"
#include "QuantumGameModeBase.h"
#include "UI/Settings/GameUserSettings/QuantumGameUserSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogVideoSettingsWidget, All, All);

void UVideoSettingsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	

	auto* UserSettings = UQuantumGameUserSettings::Get();
	if (!UserSettings)
	{
		UE_LOG(LogVideoSettingsWidget, Warning, TEXT("QuantumGameUserSettings is nullptr"));
		return;
	}

	UserSettings->LoadSettings();

	const auto VideoSetting = UserSettings->GetVideoSettings();

	check(VideoSettingsContainer);
	
	VideoSettingsContainer->ClearChildren();
	

	for(auto* Setting : VideoSetting)
	{
		const auto SettingWidget = CreateWidget<USettingsOptionWidget>(this, SettingOptionWidgetClass);
		check(SettingWidget);
		SettingWidget->Init(Setting);
		VideoSettingsContainer->AddChild(SettingWidget);
	}

	check(AutoSettingsButton);

	AutoSettingsButton->OnClicked.AddDynamic(this, &UVideoSettingsWidget::OnAutoSettings);
	
	UserSettings->OnVideoSettingsUpdate.AddUObject(this, &UVideoSettingsWidget::OnVideoSettingsUpdated);

	check(ReturnButton);
	ReturnButton->OnClicked.AddDynamic(this, &UVideoSettingsWidget::OnReturnButtonClicked);
}

void UVideoSettingsWidget::OnAutoSettings()
{
	if(auto* UserSettings = UQuantumGameUserSettings::Get())
	{
		UserSettings->SetAutoSettings();
	}
}

void UVideoSettingsWidget::OnVideoSettingsUpdated()
{
	if (!VideoSettingsContainer) return;
	
	for(auto* Widget : VideoSettingsContainer->GetAllChildren())
	{
		if(auto* SettingWidget = Cast<USettingsOptionWidget>(Widget))
		{
			SettingWidget->UpdateText();
		}
	}
}

void UVideoSettingsWidget::OnReturnButtonClicked()
{
	if (!GetWorld()) return;
	const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());

	GameMode->SetMatchState(EQuantumMatchState::Setting);
}
