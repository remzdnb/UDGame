#include "Core/BaseGameInstance.h"
#include "Engine/DataTable.h"
#include "Engine.h"

UBaseGameInstance::UBaseGameInstance()
{
}

TArray<FName> UBaseGameInstance::GetGlobalDataTableRowNames()
{
	return GlobalDataTable->GetRowNames();
}

TArray<FName> UBaseGameInstance::GetCharacterDataTableRowNames()
{
	return CharacterDataTable->GetRowNames();
}

TArray<FName> UBaseGameInstance::GetBuildingDataTableRowNames()
{
	return BuildingDataTable->GetRowNames();
}

TArray<FName> UBaseGameInstance::GetWeaponDataTableRowNames()
{
	return WeaponDataTable->GetRowNames();
}

FGlobalData* UBaseGameInstance::GetGlobalDataFromRow(FName RowName) const
{
	FString ContextString;

	if (GlobalDataTable != nullptr)
	{
		FGlobalData* GlobalData = GlobalDataTable->FindRow<FGlobalData>("Default", ContextString);

		if (GlobalData)
			return GlobalDataTable->FindRow<FGlobalData>("Default", ContextString);
		else
			return nullptr;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("GameInstance : Missing Global Data Table.")));
		return nullptr;
	}
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

FBuildingData* UBaseGameInstance::GetBuildingDataFromRow(FName RowName) const
{
	FString ContextString;

	if (BuildingDataTable != nullptr)
	{
		FBuildingData* BuildingData = BuildingDataTable->FindRow<FBuildingData>(RowName, ContextString);

		if (BuildingData)
			return BuildingDataTable->FindRow<FBuildingData>(RowName, ContextString);
		else
			return nullptr;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("GameInstance : Missing Building Data Table.")));
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



