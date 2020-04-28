// UDGame
#include "Character/BaseCharacter.h"
#include "Character/BaseAIController.h"
// ItemModule
#include "ItemModule.h"
// Engine
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

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

void ABaseCharacter::Init(FName TableRowName, uint8 NewTeamID)
{
	TeamID = NewTeamID;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ABaseCharacter::EquipRangedWeapon()
{
	/*if (RangedWeapon)
	{
		EquipedWeapon = RangedWeapon;
		EquipedWeapon->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HandSocket");
	}*/
}

