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

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> SelectedCharacterWidgetBP;

protected:

	virtual void Tick(float DeltaSeconds) override;


private:

	//ABasePlayerController* OwnerPC;

	UPROPERTY()
	class USelectedCharacterWidget* SelectedCharacterWidget;
};
