#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "RangedWeapon.generated.h"

UCLASS()
class UDGAME_API ARangedWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
	uint32 ClipAmmo;

	UPROPERTY()
	uint32 StockAmmo;

	UPROPERTY()
	bool bHasInfiniteAmmo;

	UPROPERTY()
	bool bIsReloading = false;

	FTimerHandle ReloadTimerHandle;

	void AttackOnce() override;

	void SpawnProjectile(FTransform SpawnTransform);
};
