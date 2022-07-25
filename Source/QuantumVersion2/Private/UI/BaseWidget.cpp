// Quantum.All rights reserved!


#include "UI/BaseWidget.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void UBaseWidget::Show()
{
	PlayAnimation(ShowAnimation);
	UGameplayStatics::PlaySound2D(GetWorld(), WidgetOpenSound);
}
