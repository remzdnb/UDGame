// UDGame
#include "Game/BaseGameMode.h"
#include "Game/BaseGameInstance.h"
#include "Character/BaseCharacter.h"
#include "Character/BaseAIController.h"
#include "Building/CharacterStartBuilding.h"
#include "UDGameTypes.h"
// Engine
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

ABaseGameMode::ABaseGameMode()
{
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGameMode::SpawnAllCharacters()
{
	for (TActorIterator<ACharacterStartBuilding> CharacterStart(GetWorld()); CharacterStart; ++CharacterStart)
	{
		if (CharacterStart->bIsActive)
			SpawnCharacter(CharacterStart->GetSpawnTransform(), CharacterStart->Team);
	}
}

void ABaseGameMode::SpawnCharacter(FTransform SpawnTransform, ETeam Team)
{
	if (Team == ETeam::Ally)
	{
		ABaseCharacter* Character = GetWorld()->SpawnActorDeferred<ABaseCharacter>(AllyCharacterBP, SpawnTransform);
		if (Character)
		{
			Character->Init("BaseAlly", Team);
			UGameplayStatics::FinishSpawningActor(Character, SpawnTransform);
		}
	}

	if (Team == ETeam::Enemy)
	{
		ABaseCharacter* Character = GetWorld()->SpawnActorDeferred<ABaseCharacter>(EnemyCharacterBP, SpawnTransform); //const ?
		if (Character)
		{
			Character->Init("BaseEnemy", Team);
			UGameplayStatics::FinishSpawningActor(Character, SpawnTransform);
		}
	}
}