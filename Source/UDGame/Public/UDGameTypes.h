#pragma once

#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "UDGameTypes.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Ally,
	Enemy,
	Neutral
};

USTRUCT(BlueprintType)
struct FGlobalData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FGlobalData()
	{
	}
};

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly)
	float DefaultSpeed;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* BodyMesh;

	UPROPERTY(EditDefaultsOnly)
	FName RangedWeaponRowName;

	UPROPERTY(EditDefaultsOnly)
	FName MeleeWeaponRowName;
};

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseItem")
	TSubclassOf<class ABaseWeapon> WeaponBP;

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