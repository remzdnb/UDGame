#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/ComboBox.h"
#include "SelectedCharacterWidget.generated.h"

UCLASS()
class UDGAME_API USelectedCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnInitialized() override;

	void Update(bool bShouldFadeIn);

	UFUNCTION(BlueprintImplementableEvent)
	void FadeIn();

	UFUNCTION(BlueprintImplementableEvent)
	void FadeOut();

protected:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

private:

	class UBaseGameInstance* GInstance;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LevelText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* RangedWeaponCBox;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* MeleeWeaponCBox;
};
