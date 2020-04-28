#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterSelectionUpdate, ABaseCharacter*, SelectedCharacter);

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

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FCharacterSelectionUpdate OnCharacterSelectionUpdated;

protected:

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:

	class ABaseCharacter* HoveredCharacter;
	class ABaseCharacter* SelectedCharacter;

};


