// UDGame
#include "Weapon/RangedWeapon.h"
#include "Weapon/BaseProjectile.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/PawnInterface.h"
#include "Pawn/CombatComponent.h"
#include "Pawn/CharacterAIController.h"
// Engine
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ARangedWeapon::AttackOnce()
{
	Super::AttackOnce();

	FAttackResult AttackResult;

	if (BaseSkeletalMesh)
	{
		UGameplayStatics::SpawnEmitterAttached(WeaponData.MuzzleParticle, BaseSkeletalMesh, "Muzzle", FVector::ZeroVector, FRotator(90.0f, 0.0f, 0.0f));

		const FVector SpawnLocation = FVector(BaseSkeletalMesh->GetSocketLocation("Muzzle").X, BaseSkeletalMesh->GetSocketLocation("Muzzle").Y, BaseSkeletalMesh->GetSocketLocation("Muzzle").Z);
		const FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, OwnerPInterface->GetTargetActor()->GetActorLocation());
		const FTransform SpawnTransform(SpawnRotation, SpawnLocation, FVector(1.0f));

		SpawnProjectile(SpawnTransform);
	}
}

void ARangedWeapon::SpawnProjectile(FTransform SpawnTransform)
{
	const FActorSpawnParameters SpawnParameters;

	ABaseProjectile* const Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(WeaponData.ProjectileBP, SpawnTransform, this);
	if (Projectile)
	{
		FAttackResult AttackResult = Cast<IPawnInterface>(GetOwner())->GetCombatComponent()->GenerateAttackResult();
		Projectile->Init(AttackResult);
		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	}
}