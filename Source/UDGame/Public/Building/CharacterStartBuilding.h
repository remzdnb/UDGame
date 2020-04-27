#pragma once

#include "BaseBuilding.h"
#include "Components/ArrowComponent.h"
#include "CharacterStartBuilding.generated.h"

UCLASS()
class UDGAME_API ACharacterStartBuilding : public ABaseBuilding
{
	GENERATED_BODY()

public:

	ACharacterStartBuilding();

	FTransform GetSpawnTransform();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* Arrow;
	
};
