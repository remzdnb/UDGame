#include "Game/BasePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Character/BaseCharacter.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Character/BaseAIController.h"

ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	HoveredCharacter = Cast<ABaseCharacter>(Hit.Actor);
	if (HoveredCharacter)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "yes");
	}
	//else
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "no");

}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction("Select", IE_Pressed, this, &ABasePlayerController::SelectCharacter);
	//InputComponent->BindAction("MoveTo", IE_Pressed, this, &ABasePlayerController::MoveCharacter);
}

void ABasePlayerController::SelectCharacter()
{
	if (HoveredCharacter)
	{
		SelectedCharacter = HoveredCharacter;
		OnCharacterSelectionUpdated.Broadcast(SelectedCharacter);

		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Char Selected");
	}
	else
	{
		SelectedCharacter = nullptr;
		OnCharacterSelectionUpdated.Broadcast(SelectedCharacter);

		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "Char Deselected");
	}
}

void ABasePlayerController::MoveCharacter()
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
