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

	void Init(FName TableRowName, ETeam NewTeam);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	FString CharacterName;

	UPROPERTY()
	ETeam Team;

	UFUNCTION(BlueprintImplementableEvent)
	void EquipRifle_Anim();

	UFUNCTION(BlueprintImplementableEvent)
	void EquipPistol_Anim();

	UFUNCTION(BlueprintImplementableEvent)
	void EquipMelee_Anim();

	// anim interface

	void OnRifleEquiped_Anim();
	void OnPistolEquiped_Anim();
	void OnMeleeEquiped_Anim();
	void OnAttack_Anim();
	void OnReload_Anim();

private:

	class UBaseGameInstance* GInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* GroundWidgetComponent;

	// Weapons

public:

	void SetRangedWeapon(FName RowName);
	void SetMeleeWeapon(FName RowName);
	void EquipRangedWeapon();
	void EquipMeleeWeapon();

private:

	class AWeaponItem* EquipedWeapon;
	class ARangedWeapon* RangedWeapon;
	class AMeleeWeapon* MeleeWeapon;
};

