// UDGame
#include "Core/BasePlayerController.h"
#include "Core/CombatGameMode.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/CharacterAIController.h"
#include "Pawn/NavigationComponent.h"
#include "Navigation/NavManager.h"
#include "Level/NavBlock.h"
// Engine
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
//#include "..\..\Public\Core\BasePlayerController.h"


ABasePlayerController::ABasePlayerController() :
	HoveredActor(nullptr),
	SelectedActor(nullptr)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	PrimaryActorTick.bCanEverTick = true;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	GMode = Cast<ACombatGameMode>(GetWorld()->GetAuthGameMode());
	for (TActorIterator<ANavManager> NManager(GetWorld()); NManager; ++NManager)
		NavManager = *NManager;

	if (NavManager == nullptr)
		GEngine->AddOnScreenDebugMessage(52, 1.f, FColor::Green, FString::Printf(TEXT("BasePlayerController : NavManager not found.")));
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateHoveredActor();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ABasePlayerController::UpdateHoveredActor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	//AActor* HitActor = Hit.GetActor();
	IInteractionInterface* HitActorInteractionInterface = nullptr;
	if (Hit.GetActor())
		HitActorInteractionInterface = Cast<IInteractionInterface>(Hit.GetActor());

	//AActor* ActorToHover = nullptr;

	if (HitActorInteractionInterface) // If Actor is Interactable
	{
		if (Hit.GetActor() != HoveredActor)
		{
			if (HoveredActor)
				Cast<IInteractionInterface>(HoveredActor)->OnHoverStop();

			HitActorInteractionInterface->OnHoverStart();
			HoveredActor = Hit.GetActor();
		}

		//HitActorInteractionInterface->o

		/* If NavBlock
		ANavBlock* LocalNavBlock = Cast<ANavBlock>(HitActor);
		if (LocalNavBlock)
		{
			// If NavBlock is registered, highlight the registered actor
			if (LocalNavBlock->GetRegisteredActor())
				ActorToHover = LocalNavBlock->GetRegisteredActor();
			else
				ActorToHover = LocalNavBlock;
		} 

		// If Character
		ABaseCharacter* LocalCharacter = Cast<ABaseCharacter>(HitActor);
		if (LocalCharacter)
			ActorToHover = LocalCharacter;

		// Apply
		if (ActorToHover != LastHoveredActor)
		{
			if (LastHoveredActor)
				IInteractionInterface::OnHoverStop(LastHoveredActor);

			LastHoveredActor = ActorToHover;
			IInteractionInterface::Execute_OnHoverStart(LastHoveredActor);
		} */
	}
	else // If no interactable is hit, reset
	{
		if (HoveredActor && SelectedActor != HoveredActor)
		{
			Cast<IInteractionInterface>(HoveredActor)->OnHoverStop();
			HoveredActor = nullptr;
		}
	}

	//if (NewHoveredActor)
		//GEngine->AddOnScreenDebugMessage(300, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *NewHoveredActor->GetName()));
}

void ABasePlayerController::UpdateSelectedActor()
{
	if (HoveredActor && SelectedActor != HoveredActor)
	{
		SelectedActor = HoveredActor;
		Cast<IInteractionInterface>(HoveredActor)->OnSelectionStart();
		NavManager->ShowTilesInRange(SelectedActor->GetActorLocation(), 200.0f);
	}
	else
	{
		if (SelectedActor)
			Cast<IInteractionInterface>(HoveredActor)->OnSelectionStop();
		SelectedActor = nullptr;
		NavManager->HideTiles();
	}
}

/*void ABasePlayerController::OnLeftMouseButton()
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

void ABasePlayerController::OnRightMouseButton()
{
	if (!GMode || !SelectedCharacter || !LastHoveredActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("BasePlayerController - OnRightMouseButton : nullptr found :/")));
		return;
	}

	if (GMode->GetPhase() != ECombatPhase::Starting)
	{ 
		ANavBlock* NavBlock = Cast<ANavBlock>(LastHoveredActor);
		if (NavBlock) // not necessary
		{
			SelectedCharacter->GetAIController()->MoveToNavBlock(NavBlock);
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Location : %s"), *LastHoveredActor->GetActorLocation().ToCompactString()), false);
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
}*/

//GEngine->AddOnScreenDebugMessage(52, 1.f, FColor::Green, FString::Printf(TEXT("Selected: %s"), *SelectedCharacter->GetName()));
//GEngine->AddOnScreenDebugMessage(53, 1.f, FColor::Green, FString::Printf(TEXT("Last hovered: %s"), *LastHoveredActor->GetName()));
