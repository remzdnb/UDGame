// UDGame
#include "Core/BasePlayerController.h"
#include "Level/NavBlock.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/BaseAIController.h"
// Engine
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


ABasePlayerController::ABasePlayerController() :
	LastHoveredActor(nullptr)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	GetHoveredActor();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction("Select", IE_Pressed, this, &ABasePlayerController::SelectCharacter);
	//InputComponent->BindAction("MoveTo", IE_Pressed, this, &ABasePlayerController::MoveCharacter);
}

AActor* ABasePlayerController::GetHoveredActor()
{
	FHitResult Hit;
	AActor* NewHoveredActor = nullptr;

	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	NewHoveredActor = Cast<AActor>(Hit.Actor);

	/*if (NewHoveredActor)
		GEngine->AddOnScreenDebugMessage(300, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *NewHoveredActor->GetName()));*/

	if (Cast<IInteractionInterface>(NewHoveredActor)) // If new hovered actor is interactable
	{
		if (LastHoveredActor != NewHoveredActor)
		{
			if (LastHoveredActor) // Unhover last actor
			{
				IInteractionInterface::Execute_OnHoverStop(LastHoveredActor);
			}
			LastHoveredActor = NewHoveredActor;
			IInteractionInterface::Execute_OnHoverStart(LastHoveredActor);
		}
	}
	else
	{
		if (LastHoveredActor) // Unhover last actor
		{
			IInteractionInterface::Execute_OnHoverStop(LastHoveredActor);
		}
	}

	return Cast<AActor>(Hit.Actor);
}

void ABasePlayerController::OnLeft()
{
	if (Cast<ABaseCharacter>(LastHoveredActor))
	{
		SelectedCharacter = Cast<ABaseCharacter>(LastHoveredActor);
		OnCharacterSelectionUpdated.Broadcast(SelectedCharacter);
	}
	else
	{
		SelectedCharacter = nullptr;
		OnCharacterSelectionUpdated.Broadcast(SelectedCharacter);
	}
}

void ABasePlayerController::OnRight()
{
	if (SelectedCharacter && LastHoveredActor)
	{
		ANavBlock* NavBlock = Cast<ANavBlock>(LastHoveredActor);
		if (NavBlock)
		{
			if (NavBlock->IsRegistered() == false)
			{
				SelectedCharacter->GetTargetNavBlock()->UnregisterActor(); // Unregister from previous NavBlock
				SelectedCharacter->SetTargetNavBlock(NavBlock); // Character registration
				NavBlock->RegisterActor(SelectedCharacter); // NavBlock registration
				SelectedCharacter->AIController->MovePossessedCharacter(NavBlock->GetReferenceLocation()); // Move to new NavBlock - precise location will be set "manually" by the NavBlock when the character gets close
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Location : %s"), *LastHoveredActor->GetActorLocation().ToCompactString()), false);
			}
		}
	}
}

void ABasePlayerController::SelectCharacter()
{
	if (HoveredCharacter)
	{
		SelectedCharacter = HoveredCharacter;
		OnCharacterSelectionUpdated.Broadcast(SelectedCharacter);
	}
	else
	{
		SelectedCharacter = nullptr;
		OnCharacterSelectionUpdated.Broadcast(SelectedCharacter);
	}
}

void ABasePlayerController::MoveCharacter()
{
	if (SelectedCharacter)
	{
;		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		SelectedCharacter->AIController->MovePossessedCharacter(Hit.Location);
		//Cast<ABaseAIController>(SelectedCharacter->GetController())->MoveToLocation(Hit.Location);
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
	}
}

//GEngine->AddOnScreenDebugMessage(52, 1.f, FColor::Green, FString::Printf(TEXT("Selected: %s"), *SelectedCharacter->GetName()));
//GEngine->AddOnScreenDebugMessage(53, 1.f, FColor::Green, FString::Printf(TEXT("Last hovered: %s"), *LastHoveredActor->GetName()));
