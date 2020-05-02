#pragma once

#include "UDGameTypes.h"
#include "Core/InteractionInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Blueprintable)
class ABaseCharacter : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:

	ABaseCharacter();

	void Init(FName NewTableRowName, ETeam NewTeam, class ANavBlock* SpawnNavBlock);

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	class UBaseGameInstance* GInstance;

	UPROPERTY()
	class URZAnimInstance* AnimInstance;

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

	FORCEINLINE class UCombatComponent* GetCombatComponent() const { return CombatCPT; }
	FORCEINLINE class UDetectionComponent* GetDetectionComponent() const { return DetectionCPT; }
	FORCEINLINE class UStatsComponent* GetStatsComponent() const { return StatsComponent; }
	FORCEINLINE ETeam GetTeam() const { return Team; }

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* CombatCPT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UDetectionComponent* DetectionCPT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStatsComponent* StatsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UOutlineComponent* OutlineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* TopWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* GroundWidgetComponent;

	// Navigation

public:

	FORCEINLINE class ANavBlock* GetTargetNavBlock() const { return TargetNavBlock; }
	void SetTargetNavBlock(class ANavBlock* TargetNavBlock);

private:

	class ANavBlock* TargetNavBlock;

	// Inventory - Component ?

public:

	UFUNCTION() void SetRangedWeapon(FName RowName);
	UFUNCTION() void SetMeleeWeapon(FName RowName);
	UFUNCTION() void EquipRangedWeapon();
	UFUNCTION() void EquipMeleeWeapon();
	UFUNCTION() void HolsterWeapon();

private:

	UPROPERTY(Transient) class ARangedWeapon* RangedWeapon;
	UPROPERTY(Transient) class AMeleeWeapon* MeleeWeapon;
	UPROPERTY() EWeaponSlot EquipedWeapon;

	// Combat

public:

	FORCEINLINE bool GetIsDead() const { return bIsDead; }

	UFUNCTION() void StartAttacking();
	UFUNCTION() void StopAttacking();
	UFUNCTION() void TakeAttack(bool bIsHit, float Damage, bool bIsCritical);
	UFUNCTION() void Die(bool bZdead);

private:

	bool bIsDead;

	// Interaction Interface

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHoverStart();
	virtual void OnHoverStart_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHoverStop();
	virtual void OnHoverStop_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnLeftClick();
	virtual void OnLeftClick_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRightClick();
	virtual void OnRightClick_Implementation() override;
};

