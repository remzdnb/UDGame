#include "UI/CombatGameModeWidget.h"
#include "Core/CombatGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Containers/UnrealString.h"


#include "UObject/UObjectGlobals.h"

void UCombatGameModeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GMode = Cast<ACombatGameMode>(GetWorld()->GetAuthGameMode());

	NextWaveButton->OnClicked.AddDynamic(this, &UCombatGameModeWidget::OnNextWaveButtonPressed);
}

void UCombatGameModeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCombatGameModeWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (GMode)
	{
		//PhaseText->SetText(FText::FromString(GMode->GetPhase().ToString());
//UEnum* EnumPtr = FindObject<UEnum>(nullptr, "ECombatPhase", true);
//FString DisplayString = MyEnum->GetValueDisplayText((int32)value);
		//FString EnumAsString = UEnum::GetValueAsString<ECombatPhase>(GMode->GetPhase());

		PhaseText->SetText(FText::FromString("Phase : " + UEnum::GetValueAsString<ECombatPhase>(GMode->GetPhase())));
		WaveText->SetText(FText::FromString("Wave : " + FString::FromInt(GMode->GetWave())));
		EnemiesLeftText->SetText(FText::FromString("Enemies Left : " + FString::FromInt(GMode->GetAliveEnemies().Num())));

		if (GMode->GetPhase() == ECombatPhase::AllyTurn)
			NextWaveButton->SetVisibility(ESlateVisibility::Visible);
		else
			NextWaveButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCombatGameModeWidget::OnNextWaveButtonPressed()
{
	GMode->StartEnemyTurn();
}
