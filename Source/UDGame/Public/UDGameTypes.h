#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Character/BaseCharacter.h"
#include "UDGameTypes.generated.h"

USTRUCT(BlueprintType)
struct FGlobalData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TSubclassOf<ABaseCharacter> BaseCharacterBP;

	FGlobalData()
	{
	}
};