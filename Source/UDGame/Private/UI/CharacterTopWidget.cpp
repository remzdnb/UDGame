#include "UI/CharacterTopWidget.h"
#include "Character/BaseCharacter.h"
#include "Components/StatsComponent.h"
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
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(51, 1.0f, FColor::Cyan, FString::Printf(TEXT("health : %f"), CharacterReference->GetStatsComponent()->GetHealth()), false);
			GEngine->AddOnScreenDebugMessage(52, 1.0f, FColor::Cyan, FString::Printf(TEXT("maxhealth : %f"), CharacterReference->GetStatsComponent()->GetMaxHealth()), false);
		}

	}
	else
		GEngine->AddOnScreenDebugMessage(50, 15.f, FColor::Red, FString::Printf(TEXT("nn")));

}