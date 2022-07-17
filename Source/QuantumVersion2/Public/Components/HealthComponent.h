// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UCameraShakeBase;

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUANTUMVERSION2_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	   
	UHealthComponent();

	float GetHealth() {
		return Health;
	}

	
	//creating var and function to analyze players health and return true when player`s health is below 0
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return Health <= 0.0f; }
	
	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	
	bool HealPlayerFromPick(float HealthAmount);
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return Health / MaxHealth; }

protected:

	//creating max health var to keep health value not greater than 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "500.0"))
	float MaxHealth = 100.0f;
	
	virtual void BeginPlay() override;

	
	//creating a timer which will answer for our healing system
	FTimerHandle TimerHandle_Heal;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal");
	float HealRate = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal");
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal");
	float HealCount = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;

	

	
private:
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void Healing();

	void PlayCameraShake();

	void SetHealth(float NewHealth);

	void Killed(AController* KillerController);
	
};
