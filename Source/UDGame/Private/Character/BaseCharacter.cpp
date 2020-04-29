// UDGame
#include "Character/BaseCharacter.h"
#include "Character/BaseAIController.h"
#include "Weapon/RangedWeapon.h"
#include "Weapon/MeleeWeapon.h"
#include "Game/BaseGameInstance.h"
#include "Components/StatsComponent.h"
#include "UI/CharacterTopWidget.h"
#include "UDGameTypes.h"
// Engine
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ABaseCharacter::ABaseCharacter() :
	GInstance(nullptr),
	AIController(nullptr),
	RangedWeapon(nullptr),
	MeleeWeapon(nullptr),
	EquipedWeapon(EWeaponSlot::None)
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	StatsComponent = CreateDefaultSubobject<UStatsComponent>(FName("StatsComponent"));

	TopWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("TopWidget"));
	TopWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	TopWidgetComponent->SetupAttachment(RootComponent);

	GroundWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("GroundWidget"));
	GroundWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	GroundWidgetComponent->SetupAttachment(RootComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::Init(FName NewTableRowName, ETeam NewTeam)
{
	TableRowName = NewTableRowName;
	Team = NewTeam;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	GInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AIController = Cast<ABaseAIController>(GetController());

	FCharacterData* CharacterDataPtr = GInstance->GetCharacterDataFromRow(TableRowName);
	if (CharacterDataPtr)
	{
		CharacterData = *CharacterDataPtr;
		StatsComponent->Init(CharacterData.MaxHealth, CharacterData.MaxHealth);
		StatsComponent->OnHealthReachedZero.AddDynamic(this, &ABaseCharacter::Die);
		//GetCharacterMovement()->MaxWalkSpeed = CharacterData.DefaultSpeed;
	}

	UCharacterTopWidget* TopWidget = Cast<UCharacterTopWidget>(TopWidgetComponent->GetUserWidgetObject());
	TopWidget->Init(this);

	SetMeleeWeapon("LaserSword");
	SetRangedWeapon("LaserRifle");
}

void ABaseCharacter::BeginDestroy()
{
	if (RangedWeapon)
		RangedWeapon->Destroy();
	if (MeleeWeapon)
		MeleeWeapon->Destroy();

	Super::BeginDestroy(); //After?
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ABaseCharacter::SetRangedWeapon(FName RowName)
{
	if (RangedWeapon)
		RangedWeapon->Destroy();

	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(1.0f));

	ARangedWeapon* Weapon = GetWorld()->SpawnActorDeferred<ARangedWeapon>(GInstance->GetWeaponDataFromRow(RowName)->WeaponBP, SpawnTransform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (Weapon)
	{
		Weapon->Init(RowName);
		UGameplayStatics::FinishSpawningActor(Weapon, SpawnTransform);

		RangedWeapon = Weapon;
		EquipRangedWeapon();
	}
}

void ABaseCharacter::SetMeleeWeapon(FName RowName)
{
	if (MeleeWeapon)
		MeleeWeapon->Destroy();

	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(1.0f));

	AMeleeWeapon* Weapon = GetWorld()->SpawnActorDeferred<AMeleeWeapon>(GInstance->GetWeaponDataFromRow(RowName)->WeaponBP, SpawnTransform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (Weapon)
	{
		Weapon->Init(RowName);
		UGameplayStatics::FinishSpawningActor(Weapon, SpawnTransform);

		MeleeWeapon = Weapon;
		EquipMeleeWeapon();
	}
}

void ABaseCharacter::EquipRangedWeapon()
{
	if (RangedWeapon && EquipedWeapon != EWeaponSlot::Ranged)
	{
		HolsterWeapon();

		RangedWeapon->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HandSocket");
		RangedWeapon->SetVisibility(true);
		EquipedWeapon = EWeaponSlot::Ranged;
	}
}

void ABaseCharacter::EquipMeleeWeapon()
{
	if (MeleeWeapon && EquipedWeapon != EWeaponSlot::Melee)
	{
		HolsterWeapon();

		MeleeWeapon->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HandSocket");
		MeleeWeapon->SetVisibility(true);
		EquipedWeapon = EWeaponSlot::Melee;
	}
}

void ABaseCharacter::HolsterWeapon()
{
	if (EquipedWeapon == EWeaponSlot::Ranged && RangedWeapon)
	{
		RangedWeapon->SetWantsToFire(false);
		RangedWeapon->SetVisibility(false);
	}

	if (EquipedWeapon == EWeaponSlot::Melee && MeleeWeapon)
	{
		MeleeWeapon->SetWantsToFire(false);
		MeleeWeapon->SetVisibility(false);
	}
}

void ABaseCharacter::StartAttacking()
{
	if (RangedWeapon)
		RangedWeapon->SetWantsToFire(true);
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Purple, FString::Printf(TEXT("CA VEUT ATK")));

}

void ABaseCharacter::StopAttacking()
{
	if (RangedWeapon)
		RangedWeapon->SetWantsToFire(false);
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Purple, FString::Printf(TEXT("CA VEUT PU ATK")));
}
void ABaseCharacter::TakeAttack(bool bIsHit, float Damage, bool bIsCritical)
{
	if (bIsHit)
	{
		StatsComponent->SubtractHealth(Damage);
	}
}

void ABaseCharacter::Die(bool bZdead)
{
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Orange, FString::Printf(TEXT("DEAD LMAO")));

	if (bIsDead == false)
	{
		bIsDead = true;

		GetCapsuleComponent()->SetCollisionProfileName("CharacterCapsule_Dead");
		GetMesh()->SetCollisionProfileName("CharacterMesh_Dead");
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->WakeAllRigidBodies();
		GetMesh()->bBlendPhysics = true;
		AIController->Destroy();
		TopWidgetComponent->DestroyComponent();
		GroundWidgetComponent->DestroyComponent();
		//SetLifeSpan(10.0f);
		
		/*if (MeleeWeapon)
			MeleeWeapon->OnHolster();
		if (RangedWeapon)
			RangedWeapon->OnHolster();*/


	}
}

