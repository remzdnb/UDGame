#include "UI/SelectedCharacterWidget.h" // Expected First
#include "Game/BaseGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"

void USelectedCharacterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void USelectedCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	for (FName RowName : GInstance->GetWeaponDataRowNames())
	{
		RangedWeaponCBox->AddOption(RowName.ToString());
	}
}

void USelectedCharacterWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	//NameText->SetText(FText::FromString(String));
	LevelText->SetText(FText::FromString("0"));
}

void USelectedCharacterWidget::Update(bool bShouldFadeIn)
{
	if (bShouldFadeIn)
		FadeIn();
	else
		FadeOut();
}

