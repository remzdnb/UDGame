#pragma once

#include "BaseBuilding.h"
#include "UDGameTypes.h"
#include "Components/ArrowComponent.h"
#include "CharacterStartBuilding.generated.h"

UCLASS()
class UDGAME_API ACharacterStartBuilding : public ABaseBuilding
{
	GENERATED_BODY()

public:

	ACharacterStartBuilding();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	bool bIsActive;

	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	ETeam Team;

	FTransform GetSpawnTransform();
};
