// UDGame
#include "Character/BaseCharacter.h"
#include "Character/BaseAIController.h"
#include "Weapon/RangedWeapon.h"
#include "Weapon/MeleeWeapon.h"
#include "Game/BaseGameInstance.h"
#include "UDGameTypes.h"
// Engine
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ABaseCharacter::ABaseCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GroundWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("GroundWidget"));
	GroundWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	GroundWidgetComponent->SetupAttachment(RootComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABaseCharacter::Init(FName TableRowName, ETeam NewTeam)
{
	Team = NewTeam;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	GInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	SetRangedWeapon("LaserRifle");
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ABaseCharacter::OnRifleEquiped_Anim()
{
}

void ABaseCharacter::OnPistolEquiped_Anim()
{
}

void ABaseCharacter::OnMeleeEquiped_Anim()
{
}

void ABaseCharacter::OnAttack_Anim()
{
}

void ABaseCharacter::OnReload_Anim()
{
}

void ABaseCharacter::SetRangedWeapon(FName RowName)
{
	if (RangedWeapon)
		RangedWeapon->Destroy();

	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector(1.0f));
	ARangedWeapon* Weapon = GetWorld()->SpawnActorDeferred<ARangedWeapon>(GInstance->GetWeaponDataFromRow(RowName)->WeaponBP, SpawnTransform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	if (Weapon)
	{
		UGameplayStatics::FinishSpawningActor(Weapon, SpawnTransform);
		RangedWeapon = Weapon;
	}

	EquipRangedWeapon();
}

void ABaseCharacter::SetMeleeWeapon(FName RowName)
{
}

void ABaseCharacter::EquipRangedWeapon()
{
	if (RangedWeapon)
	{
		//EquipedWeapon = RangedWeapon;
		RangedWeapon->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HandSocket");
	}
}

void ABaseCharacter::EquipMeleeWeapon()
{
}

