#include "UDPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "UDCharacter.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "BaseAIController.h"

AUDPlayerController::AUDPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AUDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	HoveredCharacter = Cast<AUDCharacter>(Hit.Actor);
	if (HoveredCharacter)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "yes");
	}
	//else
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "no");

}

void AUDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction("Select", IE_Pressed, this, &AUDPlayerController::SelectCharacter);
	//InputComponent->BindAction("MoveTo", IE_Pressed, this, &AUDPlayerController::MoveCharacter);
}

void AUDPlayerController::SelectCharacter()
{
	if (HoveredCharacter)
	{
		SelectedCharacter = HoveredCharacter;
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "yes");
	}

}

void AUDPlayerController::MoveCharacter()
{
	if (SelectedCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "yes");
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		Cast<ABaseAIController>(SelectedCharacter->GetController())->MoveToLocation(Hit.Location);
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
	}
}


/////

void AUDPlayerController::MoveToMouseCursor()
{
			// Trace to see what is under the mouse cursor
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, false, Hit);

			if (Hit.bBlockingHit)
			{
				// We hit something, move there
				SetNewMoveDestination(Hit.ImpactPoint);
			}
}

void AUDPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AUDPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AUDPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AUDPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

