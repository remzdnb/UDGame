#pragma once

#include "UDGameTypes.h"
#include "UObject/Interface.h"
#include "PawnInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPawnInterface : public UInterface
{
	GENERATED_BODY()
};

class UDGAME_API IPawnInterface
{
	GENERATED_BODY()

public:

	virtual ETeam GetTeam() = 0;
	virtual class AActor* GetTargetActor() = 0;
	virtual class ABaseWeapon* GetEquipedWeapon() = 0;

	virtual class UNavigationComponent* GetNavigationComponent() = 0;
	virtual class UDetectionComponent* GetDetectionComponent() = 0;
	virtual class UCombatComponent* GetCombatComponent() = 0;
	virtual class UStatsComponent* GetStatsComponent() = 0;
	virtual class UInventoryComponent* GetInventoryComponent() = 0;
	virtual class URZMeshFlashComponent* GetMeshFlashComponent() = 0;
	virtual class URZOutlineComponent* GetOutlineComponent() = 0;

	virtual void SetWeaponAnimation(EWeaponAnimation WeaponAnimation) = 0;
	virtual void PlayAttackAnimation() = 0;
	virtual void PlayReloadAnimation() = 0;
};
