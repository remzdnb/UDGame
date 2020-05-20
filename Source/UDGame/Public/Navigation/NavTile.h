#pragma once

#include "Core/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "NavTile.generated.h"

UCLASS()
class UDGAME_API ANavTile : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	

	ANavTile();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	FTransform GetSpawnTransform();

	void Show();
	void Hide();
	void RegisterActor(AActor* ActorToRegister);
	void UnregisterActor();

	FORCEINLINE bool GetIsSpawnLocation() const { return bIsSpawnLocation; }
	FORCEINLINE uint8 GetTeamID() const { return TeamID; }
	FORCEINLINE AActor* GetRegisteredActor() const { return RegisteredActor; }

	// Interaction Interface

	void OnHoverStart() override;
	void OnHoverStop() override;
	void OnSelectionStart() override;
	void OnSelectionStop() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneCT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBoxCT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticleCT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* ArrowCT;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Settings", meta = (AllowPrivateAccess = "true"))
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Settings", meta = (AllowPrivateAccess = "true"))
	bool bIsSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Settings", meta = (AllowPrivateAccess = "true"))
	uint8 TeamID;

	UPROPERTY(Transient) AActor* RegisteredActor;
	UPROPERTY(Transient) TArray<class ACover*> RegisteredCovers;
};
