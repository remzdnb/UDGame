#include "Pawn/TurretAIController.h"
#include "Pawn/TurretBuilding.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/DetectionComponent.h"

void ATurretAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATurretAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedTurret = Cast<ATurretBuilding>(InPawn);
}

void ATurretAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PossessedTurret)
	{
		if (PossessedTurret->GetDetectionComponent()->HasDetectedCharacter())
			PossessedTurret->SetTargetLocation(PossessedTurret->GetDetectionComponent()->GetClosestDetectedCharacter()->GetActorLocation());
		/*DetectCharacters(PossessedTurret);
		if (DetectedCharacters.Num() != 0)
			PossessedTurret->SetTargetLocation(GetClosestDetectedCharacter(PossessedTurret)->GetActorLocation());*/
	}
}
