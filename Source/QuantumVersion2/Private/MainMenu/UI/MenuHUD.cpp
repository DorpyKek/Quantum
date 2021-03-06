// Quantum.All rights reserved!


#include "MainMenu/UI/MenuHUD.h"
#include "UI/BaseWidget.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (MainMenuWidgetClass)
	{
		const auto MainMenu = CreateWidget<UBaseWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenu)
		{
			MainMenu->AddToViewport();
			MainMenu->Show();
		}
	}
}
