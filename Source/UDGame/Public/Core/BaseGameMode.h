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

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		TSubclassOf<class ABaseCharacter> AllyCharacterBP;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		TSubclassOf<class ABaseCharacter> EnemyCharacterBP;

protected:

	UPROPERTY() 
	class UBaseGameInstance* GInstance;

private:

	UPROPERTY() 
	FTimerHandle DelayTimer;
};
