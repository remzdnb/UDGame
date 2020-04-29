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
	class UDataTable* WeaponDataTable;

	TArray<FName> GetWeaponDataRowNames();
	TArray<FName> GetCharacterDataRowNames();

	FWeaponData* GetWeaponDataFromRow(FName RowName) const;
	FCharacterData* GetCharacterDataFromRow(FName RowName) const;

	FGlobalData GlobalData; // ?
};
