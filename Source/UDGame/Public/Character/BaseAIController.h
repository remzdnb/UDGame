#pragma once

#include "UDGameTypes.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

UCLASS()
class UDGAME_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABaseAIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

	FORCEINLINE class ABaseCharacter* GetTargetCharacter() const { return TargetCharacter; }

protected:

	UPROPERTY()
	class ABaseCharacter* PossessedCharacter;

	UPROPERTY()
	class ABaseCharacter* TargetCharacter;

	UPROPERTY()
	TArray<class ABaseCharacter*> DetectedCharacters;

	class ABaseCharacter* FindClosestEnemyCharacter();
	bool CanMeleeAttackTarget();

};
