#include "Navigation/NavTile.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "..\..\Public\Navigation\NavTile.h"

ANavTile::ANavTile() :
	TileSize(125.0f),
	bIsSpawnLocation(false),
	TeamID(0)
{
	SceneCT = CreateDefaultSubobject<USceneComponent>(FName("SceneCT"));
	RootComponent = SceneCT;

	CollisionBoxCT = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBoxCT"));
	CollisionBoxCT->SetupAttachment(RootComponent);
	CollisionBoxCT->SetBoxExtent(FVector(TileSize / 2, TileSize / 2, 1.0f), true);
	CollisionBoxCT->SetRelativeLocation(FVector(TileSize / 2, TileSize / 2, 0.0f));
	CollisionBoxCT->ShapeColor = FColor::Purple;

	ParticleCT = CreateDefaultSubobject<UParticleSystemComponent>(FName("ParticleCT"));
	ParticleCT->SetRelativeLocation(FVector(TileSize / 2, TileSize / 2, 1.0f));
	ParticleCT->SetupAttachment(RootComponent);

	ArrowCT = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCT"));
	ArrowCT->SetRelativeLocation(FVector(TileSize / 2, TileSize / 2, 60.0f));
	ArrowCT->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = false;
}

void ANavTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ParticleCT->Deactivate();
	ParticleCT->Activate(true);


	if (bIsSpawnLocation)
	{
		ArrowCT->SetVisibility(true);
		if (TeamID == 0)
			ArrowCT->SetArrowColor(FColor::Green);
		if (TeamID == 1)
			ArrowCT->SetArrowColor(FColor::Red);
	}
	else
		ArrowCT->SetVisibility(false);
}

void ANavTile::BeginPlay()
{
	Super::BeginPlay();
}

FTransform ANavTile::GetSpawnTransform()
{
	return ArrowCT->GetComponentTransform();
}

void ANavTile::Show()
{
	ParticleCT->SetVisibility(true);
}

void ANavTile::Hide()
{
	ParticleCT->SetVisibility(false);
}

void ANavTile::RegisterActor(AActor* ActorToRegister)
{
	RegisteredActor = ActorToRegister;
}

void ANavTile::UnregisterActor()
{
	RegisteredActor = nullptr;
}

#pragma region ///// Interaction Interface ...

void ANavTile::OnHoverStart()
{
}

void ANavTile::OnHoverStop()
{
}

void ANavTile::OnSelectionStart()
{
}

void ANavTile::OnSelectionStop()
{
}

#pragma endregion