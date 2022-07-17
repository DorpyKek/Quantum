// Quantum.All rights reserved!


#include "DevStuff/DevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADevDamageActor::ADevDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creating component and making it root by default;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ADevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	

}

