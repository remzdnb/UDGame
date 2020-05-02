#include "UI/BaseHUD.h"
#include "UI/SelectedCharacterWidget.h"
#include "UI/CombatGameModeWidget.h"
#include "Core/BaseGameInstance.h"
#include "Core/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

ABaseHUD::ABaseHUD()
{
}

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	GInstance = Cast<UBaseGameInstance>(GetGameInstance());
	OwnerPC = Cast<ABasePlayerController>(GetOwner());

	SelectedCharacterWidget = CreateWidget<USelectedCharacterWidget>(GetWorld(), GInstance->GetGlobalDataFromRow("Default")->SelectedCharacterWidgetBP);
	if (SelectedCharacterWidget)
		SelectedCharacterWidget->AddToViewport();

	OwnerPC->OnCharacterSelectionUpdated.AddDynamic(this, &ABaseHUD::UpdateSelectedCharacterWidget);

	CombatGameModeWidget = CreateWidget<UCombatGameModeWidget>(GetWorld(), GInstance->GetGlobalDataFromRow("Default")->CombatGameModeWidgetBP);
	if (CombatGameModeWidget)
		CombatGameModeWidget->AddToViewport();

	/*void UGameControlsWidget::CreateWeaponSlots()
{

	for (FName RowName : RowNames)
	{
		const FString ContextString;
		const FWeaponData* WeaponData = GInstance->GetWeaponDataTable()->FindRow<FWeaponData>(RowName, ContextString);
		if (WeaponData)
		{
			UWeaponSlotWidget* WeaponSlot = CreateWidget<UWeaponSlotWidget>(GetWorld(), GInstance->GetGlobalData().WeaponSlotWidgetBP);
			WeaponSlot->Init(RowName, *WeaponData);

			if (WeaponData->Slot == EWeaponSlot::Ranged)
			{
				WeaponSlotList.Add(WeaponSlot);
				RangedWeaponsVBox->AddChild(WeaponSlot);
			}

			if (WeaponData->Slot == EWeaponSlot::Melee)
			{
				WeaponSlotList.Add(WeaponSlot);
				MeleeWeaponsVBox->AddChild(WeaponSlot);
			}
			//GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, FString::Printf(TEXT("Weapon Name : %s"), *RowName.ToString()));
		}
	}
}*/

	/*CharacterStatsWidget = CreateWidget<UCharacterStatsWidget>(GetWorld(), GameInstance->GetGlobalData().CharacterStatsWidgetBP);
	if (CharacterStatsWidget)
		CharacterStatsWidget->AddToViewport();

	GameStatsWidget = CreateWidget<UGameStatsWidget>(GetWorld(), GameInstance->GetGlobalData().GameStatsWidgetBP);
	if (GameStatsWidget)
		GameStatsWidget->AddToViewport();

	GameNotificationsWidget = CreateWidget<UGameNotificationsWidget>(GetWorld(), GameInstance->GetGlobalData().GameNotificationsWidgetBP);
	if (GameNotificationsWidget)
		GameNotificationsWidget->AddToViewport();

	GameControlsWidget = CreateWidget<UGameControlsWidget>(GetWorld(), GameInstance->GetGlobalData().GameControlsWidgetBP);
	if (GameControlsWidget)
	{
		GameControlsWidget->AddToViewport();
	}*/


	//SetGameControlsVisibility(false, false);
}

void ABaseHUD::UpdateSelectedCharacterWidget(ABaseCharacter* SelectedCharacter)
{
	if (SelectedCharacter)
		SelectedCharacterWidget->Update(true);
	else
		SelectedCharacterWidget->Update(false);

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "HUD");
}

void ABaseHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

/*
void ABaseHUD::SetGameStatsVisibility(bool bShouldToggle, bool bShouldBeVisible)
{
	if (GameStatsWidget == nullptr)
		return;

	if (bShouldToggle)
	{
		if (GameStatsWidget->IsInViewport())
			GameStatsWidget->RemoveFromParent();
		else
			GameStatsWidget->AddToViewport();
	}
	else
	{
		if (bShouldBeVisible)
		{
			if (!GameStatsWidget->IsInViewport())
				GameStatsWidget->AddToViewport();
		}
		else
		{
			if (GameStatsWidget->IsInViewport())
				GameStatsWidget->RemoveFromParent();
		}
	}
}

void ABaseHUD::SetGameControlsVisibility(bool bShouldToggle, bool bShouldBeVisible)
{
	if (GameControlsWidget == nullptr)
		return;

	if (bShouldToggle)
	{
		if (GameControlsWidget->IsInViewport())
			GameControlsWidget->RemoveFromParent();
		else
			GameControlsWidget->AddToViewport();
	}
	else
	{
		if (bShouldBeVisible)
		{
			if (!GameControlsWidget->IsInViewport())
				GameControlsWidget->AddToViewport();
		}
		else
		{
			if (GameControlsWidget->IsInViewport())
				GameControlsWidget->RemoveFromParent();
		}
	}
}

void ABaseHUD::AddGameNotification(FString Notification)
{
	if (GameNotificationsWidget == nullptr)
		return;

	if (GameNotificationsWidget->IsInViewport())
		GameNotificationsWidget->RemoveFromParent();

	GameNotificationsWidget->SetNotificationText(Notification);
	GameNotificationsWidget->AddToViewport();
}
*/
