#pragma once

#include "Blueprint/UserWidget.h"
#include "CombatGameModeWidget.generated.h"

UCLASS()
class UDGAME_API UCombatGameModeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	
protected:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

private:

	UPROPERTY()
	class ACombatGameMode* GMode;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimeText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PhaseText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WaveText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EnemiesLeftText;

	UPROPERTY(meta = (BindWidget))
	class UButton* NextWaveButton;

	UFUNCTION()
	void OnNextWaveButtonPressed();
};
