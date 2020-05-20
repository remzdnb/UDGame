// UDGame
#include "Pawn/BaseCharacter.h"
#include "Pawn/CharacterAIController.h"
#include "Pawn/NavigationComponent.h"
#include "Pawn/DetectionComponent.h"
#include "Pawn/CombatComponent.h"
#include "Pawn/StatsComponent.h"
#include "Core/BaseGameInstance.h"
#include "Core/CombatGameMode.h"
#include "Weapon/RangedWeapon.h"
#include "Weapon/MeleeWeapon.h"
#include "UI/CharacterTopWidget.h"
#include "UDGameTypes.h"
// Animation Plugin
#include "RZAnimInstance.h"
// VisualEffects Plugin
#include "RZMeshFlashComponent.h"
#include "RZOutlineComponent.h"
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
	EquipedWeapon(EWeaponSlot::None),
	bIsDead(false)
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	NavigationCPT = CreateDefaultSubobject<UNavigationComponent>(FName("NavigationCPT"));
	DetectionCPT = CreateDefaultSubobject<UDetectionComponent>(FName("DetectionCPT"));
	CombatCPT = CreateDefaultSubobject<UCombatComponent>(FName("CombatCPT"));
	StatsCPT = CreateDefaultSubobject<UStatsComponent>(FName("StatsCPT"));
	MeshFlashCT = CreateDefaultSubobject<URZMeshFlashComponent>(FName("MeshFlashCT"));
	OutlineCT = CreateDefaultSubobject<URZOutlineComponent>(FName("OutlineCT"));
	OutlineCT->RegisterSkeletalMesh(GetMesh());
	TopWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("TopWidget"));
	TopWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	TopWidgetComponent->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

void ABaseCharacter::Init(FName NewTableRowName, ETeam Team, ANavBlock* SpawnNavBlock)
{
	TableRowName = NewTableRowName;

	//NavigationCPT->Init(this, SpawnNavBlock);
	DetectionCPT->Init(this);
	CombatCPT->Init(this, Team);
	MeshFlashCT->RegisterSkeletalMesh(GetMesh());

	if (Team == ETeam::Ally)
		DetectionCPT->EnableActiveDetection();
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	GInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AnimInstance = Cast<URZAnimInstance>(GetMesh()->GetAnimInstance());
	AIController = Cast<ACharacterAIController>(GetController());

	FCharacterData* CharacterDataPtr = GInstance->GetCharacterDataFromRow(TableRowName);
	if (CharacterDataPtr)
	{
		CharacterData = *CharacterDataPtr;
		StatsCPT->Init(CharacterData.MaxHealth, CharacterData.MaxHealth);
		StatsCPT->OnHealthReachedZero.AddDynamic(this, &ABaseCharacter::Die);
		//GetCharacterMovement()->MaxWalkSpeed = CharacterData.DefaultSpeed;
	}

	UCharacterTopWidget* TopWidget = Cast<UCharacterTopWidget>(TopWidgetComponent->GetUserWidgetObject());
	TopWidget->Init(this);

	SetMeleeWeapon("LaserSword");
	SetRangedWeapon("LaserRifle");
}

void ABaseCharacter::BeginDestroy()
{
	Super::BeginDestroy();
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
	//GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Purple, FString::Printf(TEXT("CA VEUT ATK")));

}

void ABaseCharacter::StopAttacking()
{
	if (RangedWeapon)
		RangedWeapon->SetWantsToFire(false);
	//GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Purple, FString::Printf(TEXT("CA VEUT PU ATK")));
}

void ABaseCharacter::Die(bool bZdead)
{
	if (bIsDead == false)
	{
		bIsDead = true;

		AnimInstance->StopAllAnimations();
		GetCapsuleComponent()->SetCollisionProfileName("IgnoreAll");
		GetMesh()->SetCollisionProfileName("CharacterMesh");
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->WakeAllRigidBodies();
		GetMesh()->bBlendPhysics = true;

		AIController->Destroy();
		TopWidgetComponent->DestroyComponent();
		SetLifeSpan(10.0f);
		
		if (RangedWeapon)
			RangedWeapon->Destroy();
		if (MeleeWeapon)
			MeleeWeapon->Destroy();

		ACombatGameMode* GMode = Cast<ACombatGameMode>(GetWorld()->GetAuthGameMode());
		if (GMode)
		{
			GMode->UnregisterAliveCharacter(this, CombatCPT->GetTeam());
		}

		/*if (MeleeWeapon)
			MeleeWeapon->HolsterWeapon();
		if (RangedWeapon)
			RangedWeapon->Holster();*/
	}
}

#pragma region ///// Interfaces ...

void ABaseCharacter::OnHoverStart()
{
	OutlineCT->ShowHoverOutline();
}

void ABaseCharacter::OnHoverStop()
{
	OutlineCT->HideOutline();
}

void ABaseCharacter::OnSelectionStart()
{
	OutlineCT->ShowSelectionOutline();
}

void ABaseCharacter::OnSelectionStop()
{
	OutlineCT->HideOutline();
}

ETeam ABaseCharacter::GetTeam()
{
	return CombatCPT->GetTeam();
}

AActor* ABaseCharacter::GetTargetActor()
{
	return AIController->GetTargetActor();
}

ABaseWeapon* ABaseCharacter::GetEquipedWeapon()
{
	if (EquipedWeapon == EWeaponSlot::Melee)
		return MeleeWeapon;
	else if (EquipedWeapon == EWeaponSlot::Ranged)
		return RangedWeapon;
	else
		return nullptr;
}

UNavigationComponent* ABaseCharacter::GetNavigationComponent()
{
	return NavigationCPT;
}

UDetectionComponent* ABaseCharacter::GetDetectionComponent()
{
	return DetectionCPT;
}

UCombatComponent* ABaseCharacter::GetCombatComponent()
{
	return CombatCPT;
}

UStatsComponent* ABaseCharacter::GetStatsComponent()
{
	return StatsCPT;
}

UInventoryComponent* ABaseCharacter::GetInventoryComponent()
{
	return nullptr;
}

URZMeshFlashComponent* ABaseCharacter::GetMeshFlashComponent()
{
	return MeshFlashCT;
}

URZOutlineComponent* ABaseCharacter::GetOutlineComponent()
{
	return OutlineCT;
}

void ABaseCharacter::SetWeaponAnimation(EWeaponAnimation WeaponAnimation)
{

}

void ABaseCharacter::PlayAttackAnimation()
{
	AnimInstance->StartAttackAnimation();
}

void ABaseCharacter::PlayReloadAnimation()
{
	AnimInstance->StartReloadAnimation();
}

#pragma endregion
