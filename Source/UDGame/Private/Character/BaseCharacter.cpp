#include "Character/BaseCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Character/BaseAIController.h"

ABaseCharacter::ABaseCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	GroundWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("GroundWidget"));
	GroundWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	GroundWidgetComponent->SetupAttachment(RootComponent);

	//
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
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

	/*FTransform SpawnTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::ZeroVector);

	AIController = GetWorld()->SpawnActorDeferred<ABaseAIController>(ABaseAIController::StaticClass(), SpawnTransform);
	if (AIController)
	{
		AIController->Possess(this);
		UGameplayStatics::FinishSpawningActor(AIController, SpawnTransform);
	}*/
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}
