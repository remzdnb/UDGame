// UDGame
#include "Weapon/BaseWeapon.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/CharacterAIController.h"
#include "Core/BaseGameInstance.h"
#include "RZAnimInstance.h"
// Engine
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"

ABaseWeapon::ABaseWeapon()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	//RootScene->SetWorldScale3D(FVector(1.1f));
	RootComponent = RootScene;

	BaseStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseStaticMesh"));
	BaseStaticMesh->SetCollisionProfileName("IgnoreAll");
	BaseStaticMesh->SetupAttachment(RootScene);

	BaseSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseSkeletalMesh"));
	BaseSkeletalMesh->SetCollisionProfileName("IgnoreAll");
	BaseSkeletalMesh->SetupAttachment(RootScene);

	PrimaryActorTick.bCanEverTick = true;

	bIsEquiped = false;
	bWantsToFire = false;
	LastFireTime = 0.0f;
}

void ABaseWeapon::Init(FName RowName)
{
	TableRowName = RowName;
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	GInstance = Cast<UBaseGameInstance>(GetGameInstance());
	OwnerPInterface = Cast<IPawnInterface>(GetOwner());

	FWeaponData* WeaponDataPointer = GInstance->GetWeaponDataFromRow(TableRowName);
	if (WeaponDataPointer)
		WeaponData = *WeaponDataPointer;

	SetVisibility(false);
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OwnerPInterface)
	{
		if (bWantsToFire && GetWorld()->GetTimeSeconds() - LastFireTime > WeaponData.FireRate && OwnerPInterface->GetTargetActor())
			AttackOnce();
	}
}

void ABaseWeapon::SetWantsToFire(bool bNewWantsToFire)
{
	bWantsToFire = bNewWantsToFire;
}

void ABaseWeapon::AttackOnce()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
	OwnerPInterface->PlayAttackAnimation();
}

FAttackResult ABaseWeapon::GenerateAttackResult()
{
	FAttackResult AttackResult;
	uint8 HitRoll = FMath::RandRange(1, 100);
	uint8 CritRoll = FMath::RandRange(1, 100);

	if (HitRoll >= 100 - WeaponData.HitChance)
	{
		AttackResult.bIsHit = true;
		if (CritRoll >= 100 - WeaponData.CritChance)
		{
			AttackResult.bIsCritical = true;
			AttackResult.FinalDamage = WeaponData.Damage * 2;
		}
		else
		{
			AttackResult.bIsCritical = false;
			AttackResult.FinalDamage = WeaponData.Damage;
		}
	}

	return AttackResult;
}

void ABaseWeapon::SetVisibility(bool bNewVisibility)
{
	if (bNewVisibility == true)
	{
		BaseSkeletalMesh->SetVisibility(true);
		BaseStaticMesh->SetVisibility(true);
	}
	else
	{
		BaseSkeletalMesh->SetVisibility(false);
		BaseStaticMesh->SetVisibility(false);
	}
}


