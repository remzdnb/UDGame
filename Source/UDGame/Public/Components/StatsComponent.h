#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthUpdated, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthReachedZero, bool, bHasHealthReachedZero);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDGAME_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UStatsComponent();

	void Init(float MaxHealth, float HealthRegenRate);

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddHealth(float HealthToAdd);
	void SubtractHealth(float HealthToRemove);

	UPROPERTY()
	FHealthUpdated OnHealthUpdated;

	UPROPERTY()
	FHealthReachedZero OnHealthReachedZero;

	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

private:

	float Health;
	float MaxHealth;
	float HealthRegenRate;
	float Stamina;
	float MaxStamina;
};
