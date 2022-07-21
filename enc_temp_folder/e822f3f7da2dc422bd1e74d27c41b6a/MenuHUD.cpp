// Quantum.All rights reserved!


#include "MainMenu/UI/MenuHUD.h"
#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (MainMenuWidgetClass)
	{
		const auto MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenu)
		{
			MainMenu->AddToViewport();
		}
	}
}
