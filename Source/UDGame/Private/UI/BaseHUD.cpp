#include "UI/BaseHUD.h"
#include "UI/SelectedCharacterWidget.h"

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

	SelectedCharacterWidget = CreateWidget<USelectedCharacterWidget>(GetWorld(), SelectedCharacterWidgetBP);
	if (SelectedCharacterWidget)
		SelectedCharacterWidget->AddToViewport();

	//OwnerPC = Cast<ABasePlayerController>(GetOwner());

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
