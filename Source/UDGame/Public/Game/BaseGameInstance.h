#pragma once

#include "UDGameTypes.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UCLASS()
class UDGAME_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UBaseGameInstance();

	UPROPERTY(EditAnywhere)
	UDataTable* GlobalDataTable;

	UPROPERTY(EditAnywhere)
	UDataTable* WeaponDataTable;

	FWeaponData* GetWeaponDataFromRow(FName RowName) const;

	TArray<FName> GetWeaponDataRowNames();

	//UDataTable* CharacterDataTable;
	//UDataTable* WeaponDataTable;
	//FCharacterData* GetCharacterDataFromRow(FName RowName) const;
	//FWeaponData* GetWeaponDataFromRow(FName RowName) const;

	FGlobalData GlobalData;

protected:

	virtual void OnStart() override;
};
