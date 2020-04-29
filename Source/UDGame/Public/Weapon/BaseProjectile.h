#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class UDGAME_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseProjectile();

	void Init(bool bIsHittingTarget);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleDefaultsOnly)
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleDefaultsOnly)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleDefaultsOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
	class UParticleSystemComponent* Particle;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
