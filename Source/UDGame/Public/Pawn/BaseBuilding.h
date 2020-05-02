#pragma once

#include "UDGameTypes.h"
#include "GameFramework/Pawn.h"
#include "BaseBuilding.generated.h"

UCLASS()
class UDGAME_API ABaseBuilding : public APawn
{
	GENERATED_BODY()

public:

	ABaseBuilding();

	void Init(FName NewTableRowName, ETeam NewTeam);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UCombatComponent* GetCombatComponent() const { return CombatCPT; }
	FORCEINLINE class UDetectionComponent* GetDetectionComponent() const { return DetectionCPT; }

protected:

	UPROPERTY(Transient) class UBaseGameInstance* GInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneCPT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SMeshCPT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UPoseableMeshComponent* PMeshCPT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* CombatCPT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UDetectionComponent* DetectionCPT;

	UPROPERTY() FName RowName;

};
