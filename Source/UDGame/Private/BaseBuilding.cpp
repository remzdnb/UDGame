#include "BaseBuilding.h"

ABaseBuilding::ABaseBuilding()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(FName("RootScene"));
	RootComponent = RootScene;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BaseMesh"));
	BaseMesh->SetupAttachment(RootScene);

	PrimaryActorTick.bCanEverTick = true;
}

void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

