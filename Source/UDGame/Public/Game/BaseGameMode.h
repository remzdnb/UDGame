#pragma once

#include "CoreMinimal.h"
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
	void SpawnCharacter(uint8 TeamID);

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TSubclassOf<class ABaseCharacter> BaseCharacterBP;

private:

	class UBaseGameInstance* GInstance;
};
