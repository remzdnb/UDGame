#include "Building/BaseBuilding.h"

ABaseBuilding::ABaseBuilding() : TeamID(0)
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

