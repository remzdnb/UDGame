#pragma once

#include "Pawn/BaseAIController.h"
#include "TurretAIController.generated.h"

UCLASS()
class UDGAME_API ATurretAIController : public ABaseAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

protected:

	UPROPERTY(Transient) class ATurretBuilding* PossessedTurret;
};
