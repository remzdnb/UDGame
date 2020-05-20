#include "Navigation/NavComponent.h"

UNavComponent::UNavComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNavComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNavComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

