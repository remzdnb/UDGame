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

	UPROPERTY(Transient) class UBaseGameInstance* GInstance;
	UPROPERTY(Transient) class ABasePlayerController* OwnerPC;

	UPROPERTY(Transient) class USelectedCharacterWidget* SelectedCharacterWidget;
	UPROPERTY(Transient) class UCombatGameModeWidget* CombatGameModeWidget;

	void CreateWidgets();
};
