#pragma once

#include "UDGameTypes.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UCLASS()
class UDGAME_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UBaseGameInstance();

	UPROPERTY(EditAnywhere)
	class UDataTable* GlobalDataTable;

	UPROPERTY(EditAnywhere)
	class UDataTable* CharacterDataTable;

	UPROPERTY(EditAnywhere)
	class UDataTable* BuildingDataTable;

	UPROPERTY(EditAnywhere)
	class UDataTable* WeaponDataTable;

	TArray<FName> GetGlobalDataTableRowNames();
	TArray<FName> GetCharacterDataTableRowNames();
	TArray<FName> GetBuildingDataTableRowNames();
	TArray<FName> GetWeaponDataTableRowNames();

	FGlobalData* GetGlobalDataFromRow(FName RowName) const;
	FCharacterData* GetCharacterDataFromRow(FName RowName) const;
	FBuildingData* GetBuildingDataFromRow(FName RowName) const;
	FWeaponData* GetWeaponDataFromRow(FName RowName) const;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* OutlineMaterial;
};
