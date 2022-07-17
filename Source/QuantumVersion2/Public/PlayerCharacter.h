// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "QuantumBaseCharacter.h"
#include "PlayerCharacter.generated.h"



class UCameraComponent;
class USpringArmComponent;
class USphereComponent;
/**
 * 
 */
UCLASS()
class QUANTUMVERSION2_API APlayerCharacter : public AQuantumBaseCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter(const FObjectInitializer& ObjInit);

	
protected:
	//creating component which is goint to allow us to use camera with spring arm
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Components")
	USpringArmComponent* SpringArmComponent;

	//creting property and component with blueprint read and write availiable 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* CameraCollisionComponent;

	virtual void OnDeath() override;
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void OnSprintStart();
	void OnSprintEnd();
	
	UFUNCTION()
	void OnCameraBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnCameraEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

	void CheckCameraOverlap();
};
