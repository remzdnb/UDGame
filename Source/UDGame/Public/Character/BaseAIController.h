#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	MovingToObjective,
	AttackingObjective,
	AttackingCharacter
};

UCLASS()
class UDGAME_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABaseAIController();

	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;
};
