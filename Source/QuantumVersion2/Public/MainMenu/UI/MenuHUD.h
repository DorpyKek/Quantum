// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Menu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;


};
