#include "Pawn/BaseAIController.h"

ABaseAIController::ABaseAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

