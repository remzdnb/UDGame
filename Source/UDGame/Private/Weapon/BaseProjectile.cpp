// UDGame
#include "Weapon/BaseProjectile.h"
#include "Weapon/BaseWeapon.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/CombatComponent.h"
// Engine
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ABaseProjectile::ABaseProjectile()
{
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(FName("CollisionSphere"));
	CollisionSphere->InitSphereRadius(1.0f);
	//CollisionSphere->bTraceComplexOnMove = true;
	CollisionSphere->SetCollisionProfileName("Projectile");
	RootComponent = CollisionSphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetCollisionProfileName("IgnoreAll");
	Mesh->SetupAttachment(RootComponent);

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle"));
	Particle->SetCollisionProfileName("IgnoreAll");
	Particle->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionSphere;
	ProjectileMovement->InitialSpeed = 10000.0f;
	ProjectileMovement->MaxSpeed = 10000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 5.0f;
}

void ABaseProjectile::Init(FAttackResult InAttackResult)
{
	AttackResult = InAttackResult;

	CollisionSphere->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlap);

	//if (AttackResult.bIsHit)
		//CollisionSphere->SetCollisionProfileName("Projectile");
	//else
		//CollisionSphere->SetCollisionProfileName("IgnoreAll");
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();


}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Hit")));
}

void ABaseProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Overlap")));

	//if (AttackResult.Target)
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("AttackResult.Target : %s"), *AttackResult.Target->GetName()));
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("OtherActor : %s"), *OtherActor->GetName()));

	if (AttackResult.Target == OtherActor)
	{
		IPawnInterface* TargetPInterface = Cast<IPawnInterface>(OtherActor);
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("1")));
		//UCombatComponent* CombatCPT = Cast<UCombatComponent>(OtherActor);
		if (TargetPInterface)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("2")));
			TargetPInterface->GetCombatComponent()->ApplyAttack(AttackResult);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AttackResult.Weapon->GetWeaponData().CharacterImpactParticle, GetActorLocation(), GetActorRotation());
			Destroy();
		}
	}
}

//GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *HitComponent->GetName()));