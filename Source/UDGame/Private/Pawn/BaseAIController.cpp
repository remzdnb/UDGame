// UDGame
#include "Pawn/BaseAIController.h"
#include "Pawn/BaseCharacter.h"
#include "UDGameTypes.h"
// Engine
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

#include "DrawDebugHelpers.h"


ABaseAIController::ABaseAIController() : 
	bIsMoving(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAIController::MovePossessedCharacter(FVector NewTargetLocation)
{
	bIsMoving = true;
	TargetLocation = NewTargetLocation;
	//MoveToLocation(NewTargetLocation);
}

/*void ABaseAIController::RotateToTarget()
{
	if (PossessedCharacter && TargetCharacter)
	{
		FRotator Rot = FMath::Lerp(PossessedCharacter->GetActorRotation(), UKismetMathLibrary::FindLookAtRotation(PossessedCharacter->GetActorLocation(), TargetCharacter->GetActorLocation()), 0.1f);
		PossessedCharacter->SetActorRotation(Rot);
	}

	//PossessedCharacter->SetActorRotation(UKismeth)
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
}*/


