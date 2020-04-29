// UDGame
#include "Weapon/BaseWeapon.h"
#include "Character/BaseCharacter.h"
#include "Character/BaseAIController.h"
#include "Game/BaseGameInstance.h"
// Engine
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"

ABaseWeapon::ABaseWeapon()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->SetWorldScale3D(FVector(1.1f));
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
	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	FWeaponData* WeaponDataPointer = GInstance->GetWeaponDataFromRow(TableRowName);
	if (WeaponDataPointer)
		WeaponData = *WeaponDataPointer;

	SetVisibility(false);
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (OwnerCharacter)
	{
		if (GetWorld()->GetTimeSeconds() - LastFireTime > WeaponData.FireRate && OwnerCharacter->AIController->GetTargetCharacter())
		{
			GEngine->AddOnScreenDebugMessage(5, 0.1f, FColor::Red, FString::Printf(TEXT("CA TIRE")));
			FireOnce();
		}
	}
}

void ABaseWeapon::SetWantsToFire(bool bNewWantsToFire)
{
	bWantsToFire = bNewWantsToFire;
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

void ABaseWeapon::FireOnce()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
}


