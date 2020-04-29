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

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	None,
	Ranged,
	Melee
};

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	Disabled,
	Ready,
	Firing,
	Reloading
};

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseWeapon")
	TSubclassOf<class ABaseWeapon> WeaponBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseWeapon")
	TSubclassOf<class ABaseProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseWeapon")
	FString DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseWeapon")
	EWeaponSlot WeaponSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseWeapon")
	float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseWeapon")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseWeapon")
	float CritChance;

	FWeaponData()
	{
		DisplayName = "None";
		WeaponSlot = EWeaponSlot::None;
		FireRate = 0.2f;
		Damage = 100.0f;
		CritChance = 0.1f;
	}
};

/*#define print(text)                         if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::White, TEXT(text), false)
#define printc(channel, text)               if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::White, TEXT(text))
#define printf(format, ...)                 if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::White, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#define printcf(channel, format, ...)       if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::White, FString::Printf(TEXT(format), ##__VA_ARGS__))
 
#define printwarn(text)                     if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, TEXT(text), false)
#define printcwarn(channel, text)           if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Yellow, TEXT(text))
#define printfwarn(format, ...)             if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#define printcfwarn(channel, format, ...)   if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Yellow, FString::Printf(TEXT(format), ##__VA_ARGS__))
 
#define printerr(text)                      if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, TEXT(text), false)
#define printcerr(channel, text)            if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Red, TEXT(text))
#define printferr(format, ...)              if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, FString::Printf(TEXT(format), ##__VA_ARGS__), false)
#define printcferr(channel, format, ...)    if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Red, FString::Printf(TEXT(format), ##__VA_ARGS__))
 
#define printfloat(variable)                if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Cyan, FString::Printf(TEXT(#variable ": %f"), variable), false)
#define printcfloat(channel, variable)      if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Cyan, FString::Printf(TEXT(#variable ": %f"), variable))
 
#define printvector(variable)               if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, FString::Printf(TEXT(#variable ": %s"), *variable.ToCompactString()), false)
#define printcvector(channel, variable)     if (GEngine) GEngine->AddOnScreenDebugMessage(channel, 1.5f, FColor::Green, FString::Printf(TEXT(#variable ": %s"), *variable.ToCompactString()))*/