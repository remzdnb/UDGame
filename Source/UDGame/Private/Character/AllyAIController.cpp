#include "Character/AllyAIController.h"
#include "Character/BaseCharacter.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"

void AAllyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AAllyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PossessedCharacter)
		UpdateAllyAI();
}

void AAllyAIController::UpdateAllyAI()
{
	UpdateDetectedCharacters();
	SelectTargetCharacter();

	if (TargetCharacter)
	{
		if (CanMeleeAttackTarget())
			PossessedCharacter->EquipMeleeWeapon();
		else
			PossessedCharacter->EquipRangedWeapon();

		PossessedCharacter->StartAttacking();
	}
	else
		PossessedCharacter->StopAttacking();
}

void AAllyAIController::UpdateDetectedCharacters()
{
	for (TActorIterator<ABaseCharacter> ItrCharacter(GetWorld()); ItrCharacter; ++ItrCharacter)
	{
		if (ItrCharacter->Team == ETeam::Enemy)
		{
			FHitResult OutHit;
			FCollisionQueryParams CollisionParams;
			FVector Start = FVector(PossessedCharacter->GetActorLocation().X, PossessedCharacter->GetActorLocation().Y, 150.0f);
			FVector End = FVector(ItrCharacter->GetActorLocation().X, ItrCharacter->GetActorLocation().Y, 150.0f);

			if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel1, CollisionParams))
			{
				if (OutHit.bBlockingHit)
				{
					DrawDebugLine(GetWorld(), Start, OutHit.Location, FColor::Green, false, 0.1f, 0, 1);

					ABaseCharacter* CurrentCharacter = Cast<ABaseCharacter>(OutHit.GetActor());
					if (CurrentCharacter)
						DetectedCharacters.Add(CurrentCharacter);

					if (GEngine) {

						GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
						GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Orange, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
						GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Yellow, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));

					}
				}
			}
		}
	}
}

void AAllyAIController::SelectTargetCharacter()
{
	float MinDistance = 9999999.9f;
	ABaseCharacter* CharacterRef = nullptr;

	for (ABaseCharacter* CurrentCharacter : DetectedCharacters)
	{
		if (FVector::Dist(PossessedCharacter->GetActorLocation(), CurrentCharacter->GetActorLocation()) < MinDistance)
		{
			CharacterRef = CurrentCharacter;
			MinDistance = FVector::Dist(PossessedCharacter->GetActorLocation(), CurrentCharacter->GetActorLocation());
		}
	}

	TargetCharacter = CharacterRef;
}
