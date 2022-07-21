// Quantum.All rights reserved!


#include "MainMenu/UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "QuantumGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "MainMenu/UI/LevelSelectorWidget.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::StartGame);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
	}

	CreateLevelItems();
}

void UMainMenuWidget::StartGame()
{
	const auto GameInstance = GetMyGameInstance();
	if (!GameInstance) return;

	UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetStartupLevel().LevelName);
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMainMenuWidget::CreateLevelItems()
{
	const auto GameInstance = GetMyGameInstance();
	if (!GameInstance) return;
	
	checkf(GameInstance->GetLevelsData().Num() != 0 , TEXT("No levels data"));

	if (!LevelSelectorBox) return;
	LevelSelectorBox->ClearChildren();
	
	for(auto LevelData : GameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<ULevelSelectorWidget>(GetWorld(), LevelItemClass);
		if (!LevelItemWidget) continue;

		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this, &UMainMenuWidget::OnLevelSelected); 

		LevelSelectorBox->AddChild(LevelItemWidget);
		LevelSelectorWidgets.Add(LevelItemWidget);
	}

	if (GameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(GameInstance->GetLevelsData()[0]);
	}
	else
	{
		OnLevelSelected(GameInstance->GetStartupLevel());
	}
}

void UMainMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto GameInstance = GetMyGameInstance();
	if (!GameInstance) return;

	GameInstance->SetStartupLevel(Data);

	for(auto LevelItemWidget : LevelSelectorWidgets)
	{
		if (LevelItemWidget)
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

UQuantumGameInstance* UMainMenuWidget::GetMyGameInstance() const
{
	if (!GetWorld()) return nullptr;

	return GetWorld()->GetGameInstance<UQuantumGameInstance>();
}



