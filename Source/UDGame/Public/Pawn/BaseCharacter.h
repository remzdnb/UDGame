#pragma once

#include "UDGameTypes.h"
#include "Core/InteractionInterface.h"
#include "Pawn/PawnInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Blueprintable)
class ABaseCharacter : public ACharacter, public IInteractionInterface, public IPawnInterface
{
	GENERATED_BODY()

public:

	ABaseCharacter();

	void Init(FName NewTableRowName, ETeam Team, class ANavBlock* SpawnNavBlock);

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UNavigationComponent* GetNavigationComponent() const { return NavigationCPT; }
	FORCEINLINE class UCombatComponent* GetCombatComponent() const { return CombatCPT; }
	FORCEINLINE class UDetectionComponent* GetDetectionComponent() const { return DetectionCPT; }
	FORCEINLINE class UStatsComponent* GetStatsComponent() const { return StatsCPT; }
	FORCEINLINE class ACharacterAIController* GetAIController() const { return AIController; }
	FORCEINLINE class URZAnimInstance* GetAnimInstance() const { return AnimInstance; }

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UNavigationComponent* NavigationCPT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UDetectionComponent* DetectionCPT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* CombatCPT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStatsComponent* StatsCPT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class URZMeshFlashComponent* MeshFlashCT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class URZOutlineComponent* OutlineCT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* TopWidgetComponent;

	UPROPERTY(Transient) class UBaseGameInstance* GInstance;
	UPROPERTY(Transient) class ACharacterAIController* AIController;
	UPROPERTY(Transient) class URZAnimInstance* AnimInstance;

	UPROPERTY() FName TableRowName;
	UPROPERTY() FCharacterData CharacterData;

	// Inventory

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
	UFUNCTION() void Die(bool bZdead);

private:

	bool bIsDead;

#pragma region ///// Interfaces ...

public:

	// Interaction Interface

	void OnHoverStart() override;
	void OnHoverStop() override;
	void OnSelectionStart() override;
	void OnSelectionStop() override;

	// Pawn Interface

	ETeam GetTeam() override;
	AActor* GetTargetActor() override;
	class ABaseWeapon* GetEquipedWeapon() override;

	class UNavigationComponent* GetNavigationComponent() override;
	class UDetectionComponent* GetDetectionComponent() override;
	class UCombatComponent* GetCombatComponent() override;
	class UStatsComponent* GetStatsComponent() override;
	class UInventoryComponent* GetInventoryComponent() override;
	class URZMeshFlashComponent* GetMeshFlashComponent() override;
	class URZOutlineComponent* GetOutlineComponent() override;

	virtual void SetWeaponAnimation(EWeaponAnimation WeaponAnimation) override;
	virtual void PlayAttackAnimation() override;
	virtual void PlayReloadAnimation() override;

#pragma endregion

};

