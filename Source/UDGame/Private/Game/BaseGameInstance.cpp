#include "Game/BaseGameInstance.h"
#include "Engine.h"

UBaseGameInstance::UBaseGameInstance()
{
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
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("GameInstance : Weapon Row Not Found : %s"), *RowName.ToString()));
			return nullptr;
		}
	}
	else
		return nullptr;
}

TArray<FName> UBaseGameInstance::GetWeaponDataRowNames()
{
	return WeaponDataTable->GetRowNames();
}

void UBaseGameInstance::OnStart()
{

}
