#pragma once

#include "Core/InteractionInterface.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterSelectionUpdate, ABaseCharacter*, SelectedCharacter);

UCLASS()
class ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ABasePlayerController();

	UFUNCTION(BlueprintCallable) void UpdateHoveredActor();
	UFUNCTION(BlueprintCallable) void UpdateSelectedActor();

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FCharacterSelectionUpdate OnCharacterSelectionUpdated;

protected:

	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:

	UPROPERTY(Transient) class ACombatGameMode* GMode;
	UPROPERTY(Transient) class ANavManager* NavManager;

	UPROPERTY(Transient) AActor* HoveredActor;
	UPROPERTY(Transient) AActor* SelectedActor;
};


