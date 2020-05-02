#include "Pawn/CombatComponent.h"
#include "UDGameTypes.h"

UCombatComponent::UCombatComponent() :
	Team(ETeam::Ally)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::Init(AActor* InParentActor, ETeam NewTeam)
{
	Team = NewTeam;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

