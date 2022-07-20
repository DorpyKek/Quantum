// Quantum.All rights reserved!


#include "MainMenu/UI/LevelSelectorWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void ULevelSelectorWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;
	if (LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
	}
	
	if (LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelImage);
	}
}

void ULevelSelectorWidget::SetSelected(bool IsSelected)
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void ULevelSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelButton)
	{
		LevelButton->OnClicked.AddDynamic(this, &ULevelSelectorWidget::OnLevelButtonClicked);
	}
}

void ULevelSelectorWidget::OnLevelButtonClicked()
{
	OnLevelSelected.Broadcast(LevelData);
}
