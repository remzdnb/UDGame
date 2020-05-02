// UDGame
#include "Weapon/BaseProjectile.h"
#include "Pawn/BaseCharacter.h"
// Engine
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"


ABaseProjectile::ABaseProjectile()
{
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(FName("CollisionSphere"));
	CollisionSphere->InitSphereRadius(1.0f);
	CollisionSphere->bTraceComplexOnMove = true;
	CollisionSphere->SetCollisionProfileName("IgnoreAll");
	RootComponent = CollisionSphere;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionSphere;
	ProjectileMovement->InitialSpeed = 10000.0f;
	ProjectileMovement->MaxSpeed = 10000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetCollisionProfileName("IgnoreAll");
	Mesh->SetupAttachment(RootComponent);

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle"));
	Particle->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 5.0f;
}

void ABaseProjectile::Init(bool bIsHittingTarget)
{
	if (bIsHittingTarget)
		CollisionSphere->SetCollisionProfileName("AllyProjectile");
	else
		CollisionSphere->SetCollisionProfileName("IgnoreAll");
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlap);
}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ABaseCharacter* TargetCharacter = Cast<ABaseCharacter>(OtherActor);
	if (TargetCharacter)
	{
		TargetCharacter->TakeAttack(true, 100.0f, false);
	}

	Destroy();
}

void ABaseProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

