#pragma once

#include "UDGameTypes.h"
#include "Core/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "NavBlock.generated.h"

UCLASS()
class UDGAME_API ANavBlock : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	

	ANavBlock();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE bool GetIsSpawnEnabled() const { return bIsSpawnEnabled; }
	FORCEINLINE ETeam GetTeam() const { return Team; }

	bool IsRegistered();
	void RegisterActor(AActor* ActorToRegister);
	void UnregisterActor();
	void RegisterCover(class ACover* Cover);

	FVector GetReferenceLocation();
	FTransform GetSpawnTransform();

	// Interaction Interface

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

	//

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
