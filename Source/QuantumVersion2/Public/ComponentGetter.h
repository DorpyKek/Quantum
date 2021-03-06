#pragma once
#include "GameCore/QuantumPlayerState.h"



class UComponentGetter
{
public:
	template <typename T>
	static T* GetPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;
		
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast <T>(Component);
	}

	bool static AreEnemies(AController* Controller1, AController* Controller2)
	{
		if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;
		
		const auto PlayerState1 = Cast<AQuantumPlayerState>(Controller1->PlayerState);
		const auto PlayerState2 = Cast<AQuantumPlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamId() != PlayerState2->GetTeamId();
	}
};
