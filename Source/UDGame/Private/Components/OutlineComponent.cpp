#include "Components/OutlineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

UOutlineComponent::UOutlineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOutlineComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UOutlineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UOutlineComponent::RegisterSkeletalMesh(USkeletalMeshComponent* NewSkeletalMesh)
{
	SkeletalMesh = NewSkeletalMesh;
}

void UOutlineComponent::RegisterStaticMesh(UStaticMeshComponent* NewStaticMesh)
{
	StaticMesh = NewStaticMesh;
}

void UOutlineComponent::SetStencilValue(float NewStencilValue)
{
}

void UOutlineComponent::ShowOutline()
{
	if (SkeletalMesh)
	{
		SkeletalMesh->SetRenderCustomDepth(true);
		SkeletalMesh->SetCustomDepthStencilValue(2);
	}
	if (StaticMesh)
	{
		StaticMesh->SetRenderCustomDepth(true);
		StaticMesh->SetCustomDepthStencilValue(2);
	}
}

void UOutlineComponent::HideOutline()
{
	if (SkeletalMesh)
		SkeletalMesh->SetRenderCustomDepth(false);
	if (StaticMesh)
		StaticMesh->SetRenderCustomDepth(false);
}

