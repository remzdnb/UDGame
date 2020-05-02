#pragma once

#include "Pawn/BaseBuilding.h"
#include "TurretBuilding.generated.h"

UCLASS()
class UDGAME_API ATurretBuilding : public ABaseBuilding
{
	GENERATED_BODY()
	
public:

	ATurretBuilding();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetTargetLocation(FVector NewTargetLocation);

private:

	void RotateTurret();

	FVector TargetLocation;
};
