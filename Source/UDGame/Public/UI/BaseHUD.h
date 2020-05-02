#pragma once

#include "UI/SelectedCharacterWidget.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

UCLASS()
class UDGAME_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	ABaseHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateSelectedCharacterWidget(class ABaseCharacter* SelectedCharacter);

protected:

	virtual void Tick(float DeltaSeconds) override;

private:

	class UBaseGameInstance* GInstance;
	class ABasePlayerController* OwnerPC;

	UPROPERTY()
	class USelectedCharacterWidget* SelectedCharacterWidget;

	UPROPERTY()
	class UCombatGameModeWidget* CombatGameModeWidget;
};
