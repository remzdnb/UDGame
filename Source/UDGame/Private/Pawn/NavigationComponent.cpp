// UDGame
#include "Pawn/NavigationComponent.h"
#include "Level/NavBlock.h"
// Engine
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

UNavigationComponent::UNavigationComponent() :
	MoveStepsLeft(4),
	bIsInPosition(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNavigationComponent::Init(AActor* InParentActor, ANavBlock* SpawnBlock)
{
	ParentActor = InParentActor;
	RegisterToNavBlock(SpawnBlock);
}

void UNavigationComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNavigationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNavigationComponent::RegisterToNavBlock(ANavBlock* InTargetNavBlock)
{
	InTargetNavBlock->RegisterActor(ParentActor);
	TargetNavBlock = InTargetNavBlock;
}

void UNavigationComponent::UnregisterFromNavBlock()
{
	TargetNavBlock->UnregisterActor();
	TargetNavBlock = nullptr;
}

void UNavigationComponent::SetIsInPosition(bool bNewIsInPosition)
{
	bIsInPosition = bNewIsInPosition;
}
