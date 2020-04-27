#include "UDCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "BaseAIController.h"

AUDCharacter::AUDCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AUDCharacter::BeginPlay()
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

void AUDCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}
