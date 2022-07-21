// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/BaseWidget.h"
#include "PlayerStatisticsWidget.generated.h"


class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UPlayerStatisticsWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	void SetNameText(const FText& Text);
	void SetKillsText(const FText& Text);
	void SetDeathsText(const FText& Text);
	void SetTeamNumberText(const FText& Text);
	void SetPlayerImageVisibility(bool Visible);
	void SetTeamImageColor(const FLinearColor& Color);

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillsBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathsBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamNumberBlock;
	

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerIndicatorImage;

	UPROPERTY(meta = (BindWidget))
	UImage* TeamImage;
	
};
