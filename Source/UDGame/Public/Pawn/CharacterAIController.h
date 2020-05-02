#pragma once

#include "CoreMinimal.h"
#include "Pawn/BaseAIController.h"
#include "CharacterAIController.generated.h"

UCLASS()
class UDGAME_API ACharacterAIController : public ABaseAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(Transient) class ABaseCharacter* PossessedCharacter;

	void UpdateAllyAI();
	void UpdateEnemyAI();
};
