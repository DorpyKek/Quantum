// Quantum.All rights reserved!


#include "MainMenu/MenuGameModeBase.h"
#include "MainMenu/MenuPlayerController.h"
#include "MainMenu/UI/MenuHUD.h"

AMenuGameModeBase::AMenuGameModeBase()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
}
