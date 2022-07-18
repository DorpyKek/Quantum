// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Weapons/RiffleWeapon.h"
#include "QuantumBaseCharacter.h"
#include "PlayerHUDWidget.generated.h"


class UWidgetAnimation;
class UHealthComponent;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const; 

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetAmmoData(FAmmoData& AmmoData) const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectator() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsWeaponUpdating() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	virtual void NativeOnInitialized() override;
	

private:
	
	UHealthComponent* GetHealthComponent() const;

	//creating new timer handle for holding our weapon switch
	FTimerHandle WeaponSwitchTimerHandle;
	float WeaponSwapTime = 0.3f;

	void OnHealthChanged(float Health,float HealthDelta);

	void OnNewPawn(APawn* Pawn);
};
