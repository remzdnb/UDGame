#include "Level/NavBlock.h"
#include "Level/Cover.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"
#include "Math/Vector.h"

ANavBlock::ANavBlock() :
	bIsSpawnEnabled(false),
	Team(ETeam::Neutral)
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseStaticMesh"));
	BaseMesh->SetCollisionProfileName("BlockAll");
	BaseMesh->SetupAttachment(RootScene);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionProfileName("IgnoreAll");
	CollisionBox->SetupAttachment(RootScene);

	SquareParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SquareParticle"));
	SquareParticle->SetupAttachment(RootScene);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	DirectionArrow->SetupAttachment(RootScene);

	PrimaryActorTick.bCanEverTick = true;
}

void ANavBlock::BeginPlay()
{
	Super::BeginPlay();

}

void ANavBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RegisteredActor)
	{
		if (FVector::Dist(RegisteredActor->GetActorLocation(), DirectionArrow->GetComponentLocation()) < 50.0f)
		{
			RegisteredActor->SetActorLocation(FMath::Lerp(RegisteredActor->GetActorLocation(), DirectionArrow->GetComponentLocation(), 0.5f));
		}
	}

}

bool ANavBlock::IsRegistered()
{
	if (RegisteredActor)
		return true;
	else
		return false;
}

void ANavBlock::RegisterActor(AActor* ActorToRegister)
{
	RegisteredActor = ActorToRegister;
}

void ANavBlock::UnregisterActor()
{
	RegisteredActor = nullptr;
}

void ANavBlock::RegisterCover(ACover* Cover)
{
	RegisteredCovers.Add(Cover);
}

FVector ANavBlock::GetReferenceLocation()
{
	return DirectionArrow->GetComponentLocation();
}

FTransform ANavBlock::GetSpawnTransform()
{
	return DirectionArrow->GetComponentTransform();
}

// Interaction Interface

void ANavBlock::OnHoverStart_Implementation()
{
	for (ACover* Cover : RegisteredCovers)
		IInteractionInterface::Execute_OnHoverStart(Cover);
}

void ANavBlock::OnHoverStop_Implementation()
{
	for (ACover* Cover : RegisteredCovers)
		IInteractionInterface::Execute_OnHoverStop(Cover);
}

void ANavBlock::OnLeftClick_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("left"));
}

void ANavBlock::OnRightClick_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("right"));
}

//
