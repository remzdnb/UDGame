// UDGame
#include "Character/BaseAIController.h"
#include "Character/BaseCharacter.h"
#include "UDGameTypes.h"
// Engine
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"


ABaseAIController::ABaseAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedCharacter = Cast<ABaseCharacter>(InPawn);

	/*if (Cast<ABaseCharacter>(InPawn)->Team == ETeam::Ally)
	{

	}
	if (Cast<ABaseCharacter>(InPawn)->Team == ETeam::Enemy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "enemy");


	}
	*/

}
ABaseCharacter* ABaseAIController::FindClosestEnemyCharacter()
{
	for (TActorIterator<ABaseCharacter> ItrCharacter(GetWorld()); ItrCharacter; ++ItrCharacter)
	{
		if (ItrCharacter->Team != PossessedCharacter->Team)
		{
			return *ItrCharacter;
		}
	}

	return nullptr;
}

bool ABaseAIController::CanMeleeAttackTarget()
{
	if (TargetCharacter)
	{
		if (FVector::Dist(TargetCharacter->GetActorLocation(), PossessedCharacter->GetActorLocation()) < 200.0f)
			return true;
		else
			return false;
	}

	return false;
}


