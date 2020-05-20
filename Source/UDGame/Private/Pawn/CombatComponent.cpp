// UDGame
#include "Pawn/CombatComponent.h"
#include "Pawn/StatsComponent.h"
#include "Pawn/PawnInterface.h"
#include "Core/BaseGameInstance.h"
#include "Weapon/BaseWeapon.h"
#include "UDGameTypes.h"
// VisualEffectsPlugin
#include "RZMeshFlashComponent.h"
// Engine
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

UCombatComponent::UCombatComponent() :
	Team(ETeam::Ally)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::Init(AActor* InParentActor, ETeam NewTeam)
{
	ParentActor = InParentActor;
	PawnInterface = Cast<IPawnInterface>(ParentActor);
	Team = NewTeam;

	if (!ParentActor || !PawnInterface || !GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("%s : CombatComponent/Init : nullptr found :/"), *ParentActor->GetName()));
		DestroyComponent();
		return;
	}
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

FAttackResult UCombatComponent::GenerateAttackResult()
{
	FAttackResult AttackResult;

	AttackResult.Attacker = ParentActor;
	AttackResult.Target = PawnInterface->GetTargetActor();
	AttackResult.Weapon = PawnInterface->GetEquipedWeapon();

	FWeaponData WeaponData = AttackResult.Weapon->GetWeaponData();
	uint8 HitRoll = FMath::RandRange(1, 100);
	uint8 CritRoll = FMath::RandRange(1, 100);

	if (HitRoll >= 100 - WeaponData.HitChance)
	{
		AttackResult.bIsHit = true;
		if (CritRoll >= 100 - WeaponData.CritChance)
		{
			AttackResult.bIsCritical = true;
			AttackResult.FinalDamage = WeaponData.Damage * 2;
		}
		else
		{
			AttackResult.bIsCritical = false;
			AttackResult.FinalDamage = WeaponData.Damage;
		}
	}

	return AttackResult;
}

void UCombatComponent::ApplyAttack(FAttackResult AttackResult)
{
	/*UFloatingTextWidget* FloatingTextWidget = CreateWidget<UFloatingTextWidget>(GetWorld(), Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetGlobalDataFromRow("Default")->FloatingTextWidgetBP);
	if (FloatingTextWidget)
	{
		//FloatingTextWidget->Initialize():
		FloatingTextWidget->AddToViewport();
	}*/

	if (AttackResult.bIsHit)
	{
		UStatsComponent* StatsCPT = PawnInterface->GetStatsComponent();
		if (StatsCPT)
			StatsCPT->SubtractHealth(AttackResult.FinalDamage);
	}

	PawnInterface->GetMeshFlashComponent()->StartEffect(0.05f);
}

