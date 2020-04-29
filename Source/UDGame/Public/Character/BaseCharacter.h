#pragma once

#include "UDGameTypes.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Blueprintable)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABaseCharacter();

	void Init(FName NewTableRowName, ETeam NewTeam);

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	class UBaseGameInstance* GInstance;

	UPROPERTY()
	class ABaseAIController* AIController;

	UPROPERTY()
	FString CharacterName;

	UPROPERTY()
	FName TableRowName;

	UPROPERTY()
	FCharacterData CharacterData;

	UPROPERTY()
	ETeam Team;

	UFUNCTION(BlueprintImplementableEvent)
	void EquipRifle_Anim();

	UFUNCTION(BlueprintImplementableEvent)
	void EquipPistol_Anim();

	UFUNCTION(BlueprintImplementableEvent)
	void EquipMelee_Anim();

	// Components

public:

	FORCEINLINE class UStatsComponent* GetStatsComponent() const { return StatsComponent; }

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStatsComponent* StatsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* TopWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* GroundWidgetComponent;

	// Inventory - Component ?

public:

	UFUNCTION() void SetRangedWeapon(FName RowName);
	UFUNCTION() void SetMeleeWeapon(FName RowName);
	UFUNCTION() void EquipRangedWeapon();
	UFUNCTION() void EquipMeleeWeapon();
	UFUNCTION() void HolsterWeapon();

private:

	UPROPERTY() class ARangedWeapon* RangedWeapon;
	UPROPERTY() class AMeleeWeapon* MeleeWeapon;
	UPROPERTY() EWeaponSlot EquipedWeapon;

	// Combat

public:

	UFUNCTION() void StartAttacking();
	UFUNCTION() void StopAttacking();
	UFUNCTION() void TakeAttack(bool bIsHit, float Damage, bool bIsCritical);
	UFUNCTION() void Die(bool bZdead);

private:

	bool bIsDead;
};

