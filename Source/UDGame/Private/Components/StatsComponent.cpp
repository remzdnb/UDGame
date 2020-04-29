#include "Components/StatsComponent.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UStatsComponent::Init(float NewMaxHealth, float NewHealthRegenRate)
{
	Health = NewMaxHealth;
	MaxHealth = NewMaxHealth;
	HealthRegenRate = NewHealthRegenRate;
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatsComponent::AddHealth(float HealthToAdd)
{
	float LocalHealth;

	LocalHealth = Health + HealthToAdd;
	if (LocalHealth > Health)
		Health = MaxHealth;
	else
		Health = LocalHealth;
}

void UStatsComponent::SubtractHealth(float HealthToSubtract)
{
	float LocalHealth;

	LocalHealth = Health - HealthToSubtract;
	if (LocalHealth <= 0)
	{
		Health = 0;
		OnHealthReachedZero.Broadcast(true);
	}
	else
		Health = LocalHealth;
}

