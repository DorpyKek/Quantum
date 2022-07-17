// Quantum.All rights reserved!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DevDamageActor.generated.h"

UCLASS()
class QUANTUMVERSION2_API ADevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADevDamageActor();

	//creating scene component which is goint to allow us work with our actor in scene
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	//creating two diferrent var`s for function DrawDebugSphere
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float radius = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color = FColor::Blue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFullDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType>DamageType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
