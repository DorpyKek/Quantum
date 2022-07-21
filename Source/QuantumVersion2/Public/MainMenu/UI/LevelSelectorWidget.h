// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelSelectorWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FName LevelName = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FName LevelDisplayName = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	UTexture2D* LevelImage;
};


DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelctedSignature , const FLevelData&);
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API ULevelSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnLevelSelctedSignature OnLevelSelected;

	void SetLevelData(const FLevelData& Data);
	FLevelData GetLevelData() const { return LevelData; }
	
	void SetSelected(bool IsSelected);

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LevelButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelNameTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UImage* LevelImage;

	UPROPERTY(meta = (BindWidget))
	UImage* FrameImage;

	virtual void NativeOnInitialized() override;

private:
	FLevelData LevelData;

	UFUNCTION()
	void OnLevelButtonClicked();

	UFUNCTION()
	void OnLevelHovered();

	UFUNCTION()
	void OnLevelUnHovered();
		
	
};
