// Quantum.All rights reserved!


#include "UI/GameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
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
	
	GameWidgets.Add(EQuantumMatchState::Playing, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EQuantumMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));

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
	}


	
	UE_LOG(StateLog,Error,TEXT("Match state is: %s"), *UEnum::GetValueAsString(State));
}
