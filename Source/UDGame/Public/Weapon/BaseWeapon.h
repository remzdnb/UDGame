#pragma once

#include "UDGameTypes.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class UDGAME_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseWeapon();

	void Init(FName RowName);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetWantsToFire(bool bNewWantsToFire);
	void SetVisibility(bool bNewVisibility);

	FORCEINLINE FWeaponData GetWeaponData() const { return WeaponData; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* BaseSkeletalMesh;

	UPROPERTY(Transient) class UBaseGameInstance* GInstance;
	
	class IPawnInterface* OwnerPInterface;

	FName TableRowName;
	FWeaponData WeaponData;
	bool bIsEquiped;
	bool bWantsToFire;
	float LastFireTime;

	virtual void AttackOnce();
	FAttackResult GenerateAttackResult();
};
