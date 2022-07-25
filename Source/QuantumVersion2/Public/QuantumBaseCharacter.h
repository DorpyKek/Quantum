// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "QuantumBaseCharacter.generated.h"

//using forward declaration to decalre some component class
class UHealthComponent;
class UWeaponComponent;
class USoundCue;

UCLASS()
class QUANTUMVERSION2_API AQuantumBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuantumBaseCharacter(const FObjectInitializer& ObjInit);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//creating property and component for using health component in bp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
		UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animationns")
		UAnimMontage* DeathAnimationMontage;

	//creating property of falling velocity which is goint to calculate damage depends of our velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	//this is also property which is going to calculate result of our damage and apply to our player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		FVector2D LandedDamage = FVector2D(5.0f, 80.0f);

	//creating weapon component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
		UWeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team Color")
		FName MaterialColorName = "Paint Color";

	virtual void OnDeath();

	virtual void OnHealthChanged(float Health, float DeltaHealth);

	virtual void TurnOff() override;
	virtual void Reset() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* DeathSoundCue;



public:
	


	void SetPlayerColor(const FLinearColor& Color);


private:
	
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
	
};
