#include "Pawn/CharacterAIController.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/NavigationComponent.h"
#include "Pawn/DetectionComponent.h"
#include "Pawn/PawnInterface.h"
#include "Level/NavBlock.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"

void ACharacterAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedCharacter = Cast<ABaseCharacter>(InPawn);
	NavigationCPT = Cast<IPawnInterface>(PossessedCharacter)->GetNavigationComponent();
}

void ACharacterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PossessedCharacter)
	{
		if (PossessedCharacter->GetTeam() == ETeam::Ally)
			UpdateAllyAI();
		//if (PossessedCharacter->GetTeam() == ETeam::Enemy)
			//UpdateEnemyAI();

		if (TargetActor) // Rotate character to his target
		{
			FRotator Rotator = FMath::Lerp(PossessedCharacter->GetActorRotation(), UKismetMathLibrary::FindLookAtRotation(PossessedCharacter->GetActorLocation(), TargetActor->GetActorLocation()), 0.1f);
			PossessedCharacter->SetActorRotation(Rotator);
		}
	}
}

void ACharacterAIController::UpdateAllyAI()
{
	if (!PossessedCharacter || !NavigationCPT)
		return;

	if (bWantsToMove)
	{
		TargetActor = nullptr;
		PossessedCharacter->StopAttacking();

		if (NavigationCPT->GetIsInPosition() == false)
			MoveToLocation(NavigationCPT->GetTargetNavBlock()->GetReferenceLocation(), .0f);
		else
			bWantsToMove = false;
	}
	else
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


	/*if (FVector::Dist(PossessedCharacter->GetActorLocation(), NavigationCPT->GetTargetNavBlock()->GetReferenceLocation()) <= 50.0f) // End movement if destination reached
	{
		bWantsToMove = false;
		return;
	}*/
	/*

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
		ABaseCharacter* ClosestDetectedCharacter = PossessedCharacter->GetDetectionComponent()->GetClosestDetectedCharacter();
		if (ClosestDetectedCharacter)
		{
			TargetActor = ClosestDetectedCharacter;
			PossessedCharacter->StartAttacking();
		}
		else
			PossessedCharacter->StopAttacking();
		/*ABaseCharacter* ClosestCharacter = PossessedCharacter->GetDetectionComponent()->GetClosestCharacter();
			//GetClosestCharacter(PossessedCharacter);
		
		if (ClosestCharacter)
		{
			MoveToLocation(ClosestCharacter->GetActorLocation());
			GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *ClosestCharacter->GetName()));
		}*/

	}
}

void ACharacterAIController::MoveToNavBlock(ANavBlock* InNavBlock)
{
	if (!InNavBlock || !NavigationCPT)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("CharacterAIController/MoveToNavBlock : nullptr found :/")));
		return;
	}

	if (bWantsToMove == false && InNavBlock->IsRegistered() == false)
	{
		NavigationCPT->UnregisterFromNavBlock();
		NavigationCPT->RegisterToNavBlock(InNavBlock);
		bWantsToMove = true;
	}
}