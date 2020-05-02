#include "Core/CombatGameMode.h"
#include "Core/BaseGameInstance.h"
#include "Level/NavBlock.h"
#include "Pawn/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Engine/Engine.h"


#include "Containers/EnumAsByte.h"

ACombatGameMode::ACombatGameMode() :
	Phase(ECombatPhase::Starting),
	Wave(0)
{
}

void ACombatGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ANavBlock> Block(GetWorld()); Block; ++Block) // Find and save SpawnBlocks
	{
		if (Block->GetIsSpawnEnabled())
		{
			if (Block->GetTeam() == ETeam::Ally)
				AllySpawnBlocks.Add(*Block);
			if (Block->GetTeam() == ETeam::Enemy)
				EnemySpawnBlocks.Add(*Block);
		}
	}

	SpawnAllies();
	Phase = ECombatPhase::AllyTurn;
}

void ACombatGameMode::StartEnemyTurn()
{
	if (Phase == ECombatPhase::AllyTurn)
	{
		Phase = ECombatPhase::EnemyTurn;
		SpawnEnemies();
	}
}

void ACombatGameMode::StartAllyTurn()
{
	Phase = ECombatPhase::AllyTurn;
}

void ACombatGameMode::SpawnAllies()
{
	for (ANavBlock* SpawnBlock : AllySpawnBlocks)
	{
		ABaseCharacter* Character = GetWorld()->SpawnActorDeferred<ABaseCharacter>(GInstance->GetGlobalDataFromRow("Default")->AllyCharacterBP, SpawnBlock->GetSpawnTransform());
		if (Character)
		{
			Character->Init("BaseAlly", ETeam::Ally, SpawnBlock);
			SpawnBlock->RegisterActor(Character);
			RegisterAliveCharacter(Character, ETeam::Ally);
			UGameplayStatics::FinishSpawningActor(Character, SpawnBlock->GetSpawnTransform());
		}
	}
}

void ACombatGameMode::SpawnEnemies()
{
	for (ANavBlock* SpawnBlock : EnemySpawnBlocks)
	{
		ABaseCharacter* Character = GetWorld()->SpawnActorDeferred<ABaseCharacter>(GInstance->GetGlobalDataFromRow("Default")->EnemyCharacterBP, SpawnBlock->GetSpawnTransform());
		if (Character)
		{
			Character->Init("BaseEnemy", ETeam::Enemy, SpawnBlock);
			//SpawnBlock->RegisterActor(Character);
			RegisterAliveCharacter(Character, ETeam::Enemy);
			UGameplayStatics::FinishSpawningActor(Character, SpawnBlock->GetSpawnTransform());
		}
	}
}

void ACombatGameMode::RegisterAliveCharacter(ABaseCharacter* Character, ETeam Team)
{
	if (Team == ETeam::Ally && AliveAllies.Contains(Character) == false)
		AliveAllies.Add(Character);
	if (Team == ETeam::Enemy && AliveEnemies.Contains(Character) == false)
		AliveEnemies.Add(Character);
}

void ACombatGameMode::UnregisterAliveCharacter(ABaseCharacter* Character, ETeam Team)
{
	if (Team == ETeam::Ally && AliveAllies.Contains(Character) == true)
	{
		AliveAllies.Remove(Character);
	}
	if (Team == ETeam::Enemy && AliveEnemies.Contains(Character) == true)
	{
		AliveEnemies.Remove(Character);
		if (AliveEnemies.Num() == 0 && Phase == ECombatPhase::EnemyTurn)
		{
			StartAllyTurn();
		}
	}
}
