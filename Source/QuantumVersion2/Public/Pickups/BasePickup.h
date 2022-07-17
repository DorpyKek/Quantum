// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;

UCLASS()
class QUANTUMVERSION2_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

	bool CouldBeTaken() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PickUp")
	USphereComponent* CollisionComponent;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PickUp")
	float TimeForRespawn = 5.0f;
	

private:

	virtual bool GetPickupInfo(APawn* PlayerPawn);

	void PickupTook();
	void Respawn();

	float RotationYaw = 0.0f;

	void GenerateRotation();

	FTimerHandle RespawnTimer;
	

};
