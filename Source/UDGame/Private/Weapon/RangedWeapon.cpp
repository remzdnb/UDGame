// UDGame
#include "Weapon/RangedWeapon.h"
#include "Weapon/BaseProjectile.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/BaseAIController.h"
// Engine
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ARangedWeapon::FireOnce()
{
	Super::FireOnce();

	if (BaseSkeletalMesh)
	{
		const FVector SpawnLocation = FVector(BaseSkeletalMesh->GetSocketLocation("Muzzle").X, BaseSkeletalMesh->GetSocketLocation("Muzzle").Y, BaseSkeletalMesh->GetSocketLocation("Muzzle").Z);
		const FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, OwnerCharacter->AIController->GetTargetCharacter()->GetActorLocation());
		const FTransform SpawnTransform(SpawnRotation, SpawnLocation, FVector(1.0f));
		SpawnProjectile(SpawnTransform);
	}
}

void ARangedWeapon::SpawnProjectile(FTransform SpawnTransform)
{
	const FActorSpawnParameters SpawnParameters;

	ABaseProjectile* const Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(WeaponData.ProjectileBP, SpawnTransform, this, OwnerCharacter);
	if (Projectile)
	{
		Projectile->Init(true);
		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	}
}