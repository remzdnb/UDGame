#pragma once

#include "Core/BaseGameMode.h"
#include "UDGameTypes.h"
#include "CombatGameMode.generated.h"

UENUM(BlueprintType)
enum class ECombatPhase : uint8
{
	Starting,
	AllyTurnStarting,
	AllyTurn,
	AllyTurnStopping,
	EnemyTurnStarting,
	EnemyTurn,
	EnemyTurnStopping,
	Stopping
};

UCLASS()
class UDGAME_API ACombatGameMode : public ABaseGameMode
{
	GENERATED_BODY()
	
public:

	ACombatGameMode();

	virtual void BeginPlay() override;

	void StartEnemyTurn();
	void StartAllyTurn();
	void SpawnAllies();
	void SpawnEnemies();
	void RegisterAliveCharacter(class ABaseCharacter* Character, ETeam Team);
	void UnregisterAliveCharacter(class ABaseCharacter* Character, ETeam CharacterTeam);

	FORCEINLINE ECombatPhase GetPhase() const { return Phase; }
	FORCEINLINE uint32 GetWave() const { return Wave; }
	FORCEINLINE TArray<class ABaseCharacter*> GetAliveAllies() const { return AliveAllies; }
	FORCEINLINE TArray<class ABaseCharacter*> GetAliveEnemies() const { return AliveEnemies; }

private:

	UPROPERTY(Transient) class ANavManager* NavManager;

	UPROPERTY(Transient) TArray<class ANavBlock*> AllySpawnBlocks;
	UPROPERTY(Transient) TArray<class ANavBlock*> EnemySpawnBlocks;
	UPROPERTY(Transient) TArray<class ANavTile*> AllySpawnTiles;
	UPROPERTY(Transient) TArray<class ANavTile*> EnemySpawnTiles;
	UPROPERTY(Transient) TArray<class ABaseCharacter*> AliveAllies;
	UPROPERTY(Transient) TArray<class ABaseCharacter*> AliveEnemies;

	ECombatPhase Phase;
	uint32 Wave;
};
