#pragma once

#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

UCLASS()
class UDGAME_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ABaseGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnAllCharacters();

	UFUNCTION(BlueprintCallable)
	void SpawnCharacter(FTransform SpawnTransform, ETeam Team);

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TSubclassOf<class ABaseCharacter> AllyCharacterBP;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TSubclassOf<class ABaseCharacter> EnemyCharacterBP;

private:

	class UBaseGameInstance* GInstance;
};
