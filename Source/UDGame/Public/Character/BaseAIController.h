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

protected:

	class ABaseCharacter* PossessedCharacter;

	class ABaseCharacter* FindClosestEnemyCharacter();


private:


	UPROPERTY()
	TArray<ABaseCharacter*> DetectedCharacters;
};
