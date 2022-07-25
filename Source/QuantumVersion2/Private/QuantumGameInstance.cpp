// Quantum.All rights reserved!


#include "QuantumGameInstance.h"
#include "Sound/SoundFunctionLibrary.h"

void UQuantumGameInstance::ToggleVolume()
{
	USoundFunctionLibrary::ToogleSoundClassVolume(MasterSoundClass);
}
