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

	void MoveToNavBlock(class ANavBlock* InNavBlock);

private:

	UPROPERTY(Transient) class ABaseCharacter* PossessedCharacter;
	UPROPERTY(Transient) class UNavigationComponent* NavigationCPT;

	bool bWantsToMove;

	void UpdateAllyAI();
	void UpdateEnemyAI();
};
