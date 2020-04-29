#include "Character/AllyAIController.h"
#include "Character/BaseCharacter.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

void AAllyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AAllyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateDetectedCharacters();
}

void AAllyAIController::UpdateDetectedCharacters()
{
	for (TActorIterator<ABaseCharacter> ItrCharacter(GetWorld()); ItrCharacter; ++ItrCharacter)
	{
		if (ItrCharacter->Team == ETeam::Enemy)
		{
			FHitResult OutHit;
			FCollisionQueryParams CollisionParams;
			FVector Start = PossessedCharacter->GetActorLocation();
			FVector End = ItrCharacter->GetActorLocation();

			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.1f, 0, 1);

			if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel1, CollisionParams))
			{
				if (OutHit.bBlockingHit)
				{
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
