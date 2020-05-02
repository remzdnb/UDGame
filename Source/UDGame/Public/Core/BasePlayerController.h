#pragma once

#include "Core/InteractionInterface.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterSelectionUpdate, ABaseCharacter*, SelectedCharacter);

UCLASS()
class ABasePlayerController : public APlayerController, public IInteractionInterface
{
	GENERATED_BODY()

public:

	ABasePlayerController();

	UFUNCTION(BlueprintCallable)
	void OnLeft();

	UFUNCTION(BlueprintCallable)
	void OnRight();

	UFUNCTION(BlueprintCallable)
	void SelectCharacter();

	UFUNCTION(BlueprintCallable)
	void MoveCharacter();

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FCharacterSelectionUpdate OnCharacterSelectionUpdated;

protected:

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:

	UPROPERTY() AActor* LastHoveredActor;
	UPROPERTY() class ABaseCharacter* HoveredCharacter; //Transient ?
	UPROPERTY() class ABaseCharacter* SelectedCharacter;

	AActor* GetHoveredActor();

};


