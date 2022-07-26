// Quantum.All rights reserved!


#include "UI/GameHUD.h"
#include "Engine/Canvas.h"
#include "UI/BaseWidget.h"
#include "QuantumGameModeBase.h"


DEFINE_LOG_CATEGORY_STATIC(StateLog, All, All);

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCross();
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	GameWidgets.Add(EQuantumMatchState::Playing, CreateWidget<UBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EQuantumMatchState::Pause, CreateWidget<UBaseWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EQuantumMatchState::GameOver, CreateWidget<UBaseWidget>(GetWorld(), GameOverWidgetClass));
	GameWidgets.Add(EQuantumMatchState::Setting, CreateWidget<UBaseWidget>(GetWorld(), SettingsWidget));
	GameWidgets.Add(EQuantumMatchState::VideoSetting, CreateWidget<UBaseWidget>(GetWorld(), VideoSettingsWidget));
	GameWidgets.Add(EQuantumMatchState::SoundSetting, CreateWidget<UBaseWidget>(GetWorld(), AudioSettingsWidget));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	
	if (GetWorld())
	{
		const auto GameMode = Cast<AQuantumGameModeBase>(GetWorld()->GetAuthGameMode());

		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AGameHUD::OnMatchStateChanged);
		}
	}
}

//creating the function to draw the crosshair
void AGameHUD::DrawCross()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	//creating crosshair properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
		float HalfLineSize = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
		float Thickness = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
		FLinearColor CrossColor = FLinearColor::Red;

	//drawing the crosshair
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, CrossColor, Thickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, CrossColor, Thickness);
}

void AGameHUD::OnMatchStateChanged(EQuantumMatchState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}
	
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}


	
	UE_LOG(StateLog,Error,TEXT("Match state is: %s"), *UEnum::GetValueAsString(State));
}
