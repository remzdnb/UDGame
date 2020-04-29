#include "Character/EnemyAIController.h"
#include "Character/BaseCharacter.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	//if (FindClosestEnemyCharacter())
		//MoveToActor(FindClosestEnemyCharacter());
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (FindClosestEnemyCharacter())
		MoveToActor(FindClosestEnemyCharacter());
}