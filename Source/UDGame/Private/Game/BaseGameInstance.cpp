#include "Game/BaseGameInstance.h"
#include "Engine/DataTable.h"
#include "Engine.h"

UBaseGameInstance::UBaseGameInstance()
{
}

TArray<FName> UBaseGameInstance::GetCharacterDataRowNames()
{
	return CharacterDataTable->GetRowNames();
}

TArray<FName> UBaseGameInstance::GetWeaponDataRowNames()
{
	return WeaponDataTable->GetRowNames();
}

FCharacterData* UBaseGameInstance::GetCharacterDataFromRow(FName RowName) const
{
	FString ContextString;

	if (CharacterDataTable != nullptr)
	{
		FCharacterData* CharacterData = CharacterDataTable->FindRow<FCharacterData>(RowName, ContextString);

		if (CharacterData)
			return CharacterDataTable->FindRow<FCharacterData>(RowName, ContextString);
		else
			return nullptr;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("GameInstance : Missing Character Data Table.")));
		return nullptr;
	}
}

FWeaponData* UBaseGameInstance::GetWeaponDataFromRow(FName RowName) const
{
	FString ContextString;

	if (WeaponDataTable != nullptr)
	{
		FWeaponData* WeaponData = WeaponDataTable->FindRow<FWeaponData>(RowName, ContextString);

		if (WeaponData)
			return WeaponDataTable->FindRow<FWeaponData>(RowName, ContextString);
		else
			return nullptr;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("GameInstance : Missing Weapon Data Table.")));
		return nullptr;
	}
}

//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("GameInstance : Weapon Row Not Found : %s"), *RowName.ToString()));



