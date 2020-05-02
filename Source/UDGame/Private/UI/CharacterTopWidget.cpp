#include "UI/CharacterTopWidget.h"
#include "Pawn/BaseCharacter.h"
#include "Pawn/StatsComponent.h"
#include "Components/ProgressBar.h"
#include "Engine/Engine.h"

void UCharacterTopWidget::Init(ABaseCharacter* NewCharacterReference)
{
	CharacterReference = NewCharacterReference;
}

void UCharacterTopWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCharacterTopWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (CharacterReference)
	{
		HealthBar->SetPercent(CharacterReference->GetStatsComponent()->GetHealth() / CharacterReference->GetStatsComponent()->GetMaxHealth());
	}
	else
		GEngine->AddOnScreenDebugMessage(50, 15.f, FColor::Red, FString::Printf(TEXT("nn")));

}