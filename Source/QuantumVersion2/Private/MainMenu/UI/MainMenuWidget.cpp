// Quantum.All rights reserved!


#include "MainMenu/UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "QuantumGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "QuantumGameModeBase.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "MainMenu/UI/LevelSelectorWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Settings/VideoSettingsWidget.h"
#include "Sound/SoundCue.h"

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
		QuitButton->OnHovered.AddDynamic(this, &UMainMenuWidget::OnButtonHovered);
		QuitButton->OnUnhovered.AddDynamic(this, &UMainMenuWidget::OnButtonUnhovered);
	}
	if (QuitGameTextBlock)
	{
		QuitGameTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}

	check(SettingsButton);
	SettingsButton->OnClicked.AddDynamic(this, &ThisClass::OpenSettings);
	
	CreateLevelItems();
}

void UMainMenuWidget::StartGame()
{
	PlayAnimation(LoadAnimation);
	UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnButtonHovered()
{
	PlayAnimation(QuitAnimation);
	GetWorld()->GetTimerManager().SetTimer(AnimationTimerHandle, this, &UMainMenuWidget::VisibilityShow, 1, false);
	GetWorld()->GetTimerManager().ClearTimer(AnimationTimerHandle);
	
}

void UMainMenuWidget::OnButtonUnhovered()
{
	PlayAnimationReverse(QuitAnimation);
	VisibilityClose();
	GetWorld()->GetTimerManager().ClearTimer(AnimationTimerHandle);
	
}

void UMainMenuWidget::OpenSettings()
{
	if (!GetWorld()) return;
	const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());

	GameMode->SetMatchState(EQuantumMatchState::Setting);
	
}

void UMainMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation != LoadAnimation) return;

	const auto GameInstance = GetMyGameInstance();
	if (!GameInstance) return;

	UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetStartupLevel().LevelName);
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

void UMainMenuWidget::VisibilityShow()
{
	if (QuitGameTextBlock)
	{
		QuitGameTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainMenuWidget::VisibilityClose()
{
	if (QuitGameTextBlock)
	{
		QuitGameTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
}


