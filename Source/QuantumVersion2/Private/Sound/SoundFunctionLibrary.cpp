// Quantum.All rights reserved!


#include "Sound/SoundFunctionLibrary.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(SoundFuncLibraryLog, All, All);

void USoundFunctionLibrary::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
	if (!SoundClass) return;
	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
	UE_LOG(SoundFuncLibraryLog,Display,TEXT("The volume of sound class has been changed : %s = %f"), 
		*SoundClass->GetName(), SoundClass->Properties.Volume);
}

void USoundFunctionLibrary::ToogleSoundClassVolume(USoundClass* SoundClass)
{
	if (!SoundClass) return;
	const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
	SetSoundClassVolume(SoundClass, NextVolume);
}
