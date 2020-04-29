#pragma once

#include "CoreMinimal.h"
#include "Character/BaseAIController.h"
#include "EnemyAIController.generated.h"


UCLASS()
class UDGAME_API AEnemyAIController : public ABaseAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	
};
