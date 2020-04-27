#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

UCLASS()
class ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ABasePlayerController();

	UFUNCTION(BlueprintCallable)
	void SelectCharacter();

	UFUNCTION(BlueprintCallable)
	void MoveCharacter();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

private:

	class ABaseCharacter* HoveredCharacter;

	class ABaseCharacter* SelectedCharacter;

};

