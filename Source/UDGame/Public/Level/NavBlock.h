#pragma once

#include "UDGameTypes.h"
#include "Core/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "NavBlock.generated.h"

UCLASS()
class UDGAME_API ANavBlock : public AActor
{
	GENERATED_BODY()
	
public:	

	ANavBlock();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool IsRegistered();
	void RegisterActor(AActor* ActorToRegister);
	void UnregisterActor();
	void RegisterCover(class ACover* Cover);

	FVector GetReferenceLocation();
	FTransform GetSpawnTransform();

	FORCEINLINE AActor* GetRegisteredActor() const { return RegisteredActor; }
	FORCEINLINE bool GetIsSpawnEnabled() const { return bIsSpawnEnabled; }
	FORCEINLINE ETeam GetTeam() const { return Team; }

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* SquareParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* DirectionArrow;

	UPROPERTY()
	AActor* RegisteredActor;

	UPROPERTY(Transient)
	TArray<class ACover*> RegisteredCovers;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bIsSpawnEnabled;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	ETeam Team;

};
