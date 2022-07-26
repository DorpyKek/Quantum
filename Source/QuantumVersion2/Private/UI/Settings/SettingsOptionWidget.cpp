// Quantum.All rights reserved!


#include "UI/Settings/SettingsOptionWidget.h"
#include "UI/Settings/GameUserSettings/QuantumGameSetting.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void USettingsOptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(SettingDisplayName);
	check(SettingCurrentValue);
	check(NextSettingButton);
	check(PreviousSettingButton);

	NextSettingButton->OnClicked.AddDynamic(this, &USettingsOptionWidget::OnNextSetting);
	PreviousSettingButton->OnClicked.AddDynamic(this, &USettingsOptionWidget::OnPrevSetting);
}

void USettingsOptionWidget::Init(UQuantumGameSetting* InSetting)
{
	Setting = MakeWeakObjectPtr(InSetting);
	check(Setting.IsValid());
	
	UpdateText();
}

void USettingsOptionWidget::UpdateText()
{
	if(Setting.IsValid())
	{
		SettingDisplayName->SetText(FText::FromString(Setting->GetName()));	
		SettingCurrentValue->SetText(FText::FromString(Setting->GetCurrentOption().Name));
	}
}

void USettingsOptionWidget::OnNextSetting()
{
	if(Setting.IsValid())
	{
		Setting->ApplyNextOption();
		UpdateText();
	}
}

void USettingsOptionWidget::OnPrevSetting()
{
	if(Setting.IsValid())
	{
		Setting->ApplyPrevOption();
		UpdateText();
	}
}
