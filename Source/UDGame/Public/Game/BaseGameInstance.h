#pragma once

#include "CoreMinimal.h"
#include "UDGameTypes.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "BaseGameInstance.generated.h"

UCLASS()
class UDGAME_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UBaseGameInstance();

	UPROPERTY(EditAnywhere)
	UDataTable* GlobalDataTable;

	//UDataTable* CharacterDataTable;
	//UDataTable* WeaponDataTable;
	//FCharacterData* GetCharacterDataFromRow(FName RowName) const;
	//FWeaponData* GetWeaponDataFromRow(FName RowName) const;

	FGlobalData GlobalData;
};
