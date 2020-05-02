// UDGame
#include "Core/BaseGameMode.h"
#include "Core/BaseGameInstance.h"
#include "Level/NavBlock.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/BaseAIController.h"
#include "UDGameTypes.h"
// Engine
#include "Engine/Engine.h"
#include "Engine/World.h"

ABaseGameMode::ABaseGameMode()
{
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	GInstance = Cast<UBaseGameInstance>(GetGameInstance());
}