#pragma once

#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "BaseItem.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseItem")
	TSubclassOf<ABaseItem> WeaponBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseItem")
	FString DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseItem")
	FName SocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RangedWeapon")
	float FireRate;

	FItemData()
	{
		DisplayName = "None";
		SocketName = "HandSocket";
	}
};

UCLASS()
class ITEMMODULE_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseItem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BaseSkeletalMesh;

	UPROPERTY()
	FString ItemName;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UDataTable> ItemDataTable;

	void AttachToCharacterHand(class ACharacter* TargetCharacter);

};
