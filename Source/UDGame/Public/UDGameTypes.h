#pragma once

#include "Character/BaseCharacter.h"
#include "Weapon/BaseWeapon.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
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

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseItem")
	TSubclassOf<ABaseWeapon> WeaponBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseItem")
	FString DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseItem")
	FName SocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RangedWeapon")
	float FireRate;

	FWeaponData()
	{
		DisplayName = "None";
		SocketName = "HandSocket";
	}
};