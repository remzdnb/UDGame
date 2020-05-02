#include "Pawn/CharacterAIController.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/DetectionComponent.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"

void ACharacterAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedCharacter = Cast<ABaseCharacter>(InPawn);
}

void ACharacterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PossessedCharacter)
	{
		if (PossessedCharacter->GetTeam() == ETeam::Ally)
			UpdateAllyAI();
		if (PossessedCharacter->GetTeam() == ETeam::Enemy)
			UpdateEnemyAI();
	}
}

void ACharacterAIController::UpdateAllyAI()
{
	if (PossessedCharacter)
	{
		if (PossessedCharacter->GetDetectionComponent()->HasDetectedCharacter())
		{
			TargetActor = PossessedCharacter->GetDetectionComponent()->GetClosestDetectedCharacter();
			PossessedCharacter->StartAttacking();
		}
		else
		{
			TargetActor = nullptr;
			PossessedCharacter->StopAttacking();
		}
	}

	/*if (bIsMoving)
	{ 
		if (FVector::Dist(PossessedCharacter->GetActorLocation(), TargetLocation) <= 200.0f)
		{
			bIsMoving = false;
			return;
		}

		PossessedCharacter->StopAttacking();
		MoveToLocation(TargetLocation, 0.0f);
		return;
	}

	if (TargetCharacter)
	{
		//GEngine->AddOnScreenDebugMessage(50, 1.f, FColor::Red, FString::Printf(TEXT("TChar: %s"), *TargetCharacter->GetName()));
		RotateToTarget();

		if (CanMeleeAttackTarget())
			PossessedCharacter->EquipMeleeWeapon();
		else
			PossessedCharacter->EquipRangedWeapon();

		PossessedCharacter->StartAttacking();
	}
	else
		PossessedCharacter->StopAttacking();*/
}

void ACharacterAIController::UpdateEnemyAI()
{
	if (PossessedCharacter)
	{
		ABaseCharacter* ClosestCharacter = PossessedCharacter->GetDetectionComponent()->GetClosestCharacter();
			//GetClosestCharacter(PossessedCharacter);
		
		if (ClosestCharacter)
		{
			MoveToLocation(ClosestCharacter->GetActorLocation());
			GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *ClosestCharacter->GetName()));
		}

	}
}