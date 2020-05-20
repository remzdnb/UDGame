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

	CreateWidgets();
}

void ABaseHUD::CreateWidgets()
{
	if (!GInstance || !OwnerPC || !GetWorld())
		return;

	SelectedCharacterWidget = CreateWidget<USelectedCharacterWidget>(GetWorld(), GInstance->GetGlobalDataFromRow("Default")->SelectedCharacterWidgetBP);
	if (SelectedCharacterWidget)
		SelectedCharacterWidget->AddToViewport();

	CombatGameModeWidget = CreateWidget<UCombatGameModeWidget>(GetWorld(), GInstance->GetGlobalDataFromRow("Default")->CombatGameModeWidgetBP);
	if (CombatGameModeWidget)
		CombatGameModeWidget->AddToViewport();

	OwnerPC->OnCharacterSelectionUpdated.AddDynamic(this, &ABaseHUD::UpdateSelectedCharacterWidget);
}

void ABaseHUD::UpdateSelectedCharacterWidget(ABaseCharacter* SelectedCharacter)
{
	if (SelectedCharacter)
		SelectedCharacterWidget->Update(true);
	else
		SelectedCharacterWidget->Update(false);
}

void ABaseHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}