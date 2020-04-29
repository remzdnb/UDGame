#pragma once

#include "Engine/DataTable.h"
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

	virtual void SetWantsToFire(bool bNewWantsToFire);

	void SetVisibility(bool bNewVisibility);

protected:

	virtual void FireOnce();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* BaseSkeletalMesh;

	UPROPERTY()
	class UBaseGameInstance* GInstance;

	UPROPERTY()
	class ABaseCharacter* OwnerCharacter;

	UPROPERTY()
	FName TableRowName;

	UPROPERTY()
	FWeaponData WeaponData;

	bool bIsEquiped;
	bool bWantsToFire;
	float LastFireTime;
};
