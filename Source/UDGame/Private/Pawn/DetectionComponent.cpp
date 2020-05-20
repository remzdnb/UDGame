#include "Pawn/DetectionComponent.h"
#include "Pawn/BaseCharacter.h"
#include "UDGameTypes.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

UDetectionComponent::UDetectionComponent() : 
	bIsActiveDetectionEnabled(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDetectionComponent::Init(AActor* InParentActor)
{
	ParentActor = InParentActor;
}

void UDetectionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ParentActor && bIsActiveDetectionEnabled)
		DetectVisibleCharacters(ETeam::Enemy);

	//Debug();
}

void UDetectionComponent::DetectVisibleCharacters(ETeam Team)
{
	TArray<class ABaseCharacter*> NewDetectedCharacters;

	for (TActorIterator<ABaseCharacter> LocalCharacter(GetWorld()); LocalCharacter; ++LocalCharacter)
	{
		if (LocalCharacter->GetIsDead() == false && Team == ETeam::Enemy) // ugly ass bih
		{
			TArray<FHitResult> OutHits;
			FCollisionQueryParams CollisionParams;
			FVector Start = FVector(ParentActor->GetActorLocation().X, ParentActor->GetActorLocation().Y, LocalCharacter->GetActorLocation().Z + 50.0f);
			FVector End = FVector(LocalCharacter->GetActorLocation().X, LocalCharacter->GetActorLocation().Y, LocalCharacter->GetActorLocation().Z + 50.0f);

			GetWorld()->LineTraceMultiByChannel(OutHits, Start, End, ECC_GameTraceChannel8, CollisionParams);
			for (auto& OutHit : OutHits)
			{
				ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(OutHit.GetActor());
				if (HitCharacter == *LocalCharacter)
				{
					DrawDebugLine(GetWorld(), Start, OutHit.Location, FColor::Green, false, 0.1f, 0, 1);

					NewDetectedCharacters.Add(HitCharacter);

					//DetectedCharacters.Add(HitCharacter);
					//RegisterDetectedCharacter(HitCharacter);
				}
			}
		}
	}

	for (ABaseCharacter* CurrentCharacter : DetectedCharacters)
	{
		if (NewDetectedCharacters.Contains(CurrentCharacter) == false)
			CurrentCharacter->GetDetectionComponent()->UnregisterDetectedCharacter(Cast<ABaseCharacter>(ParentActor));
	}

	for (ABaseCharacter* CurrentCharacter : NewDetectedCharacters)
	{
		if (DetectedCharacters.Contains(CurrentCharacter) == false)
			CurrentCharacter->GetDetectionComponent()->RegisterDetectedCharacter(Cast<ABaseCharacter>(ParentActor));
	}

	DetectedCharacters.Empty();
	for (ABaseCharacter* CurrentCharacter : NewDetectedCharacters)
		RegisterDetectedCharacter(CurrentCharacter);
}

ABaseCharacter* UDetectionComponent::GetClosestDetectedCharacter()
{
	ABaseCharacter* TMPCharacter = nullptr;
	float MinDistance = 9999999.9f;

	if (ParentActor)
	{
		for (ABaseCharacter* CurrentCharacter : DetectedCharacters)
		{
			if (FVector::Dist(ParentActor->GetActorLocation(), CurrentCharacter->GetActorLocation()) < MinDistance)
			{
				TMPCharacter = CurrentCharacter;
				MinDistance = FVector::Dist(ParentActor->GetActorLocation(), CurrentCharacter->GetActorLocation());
			}
		}
	}

	return TMPCharacter;
}

ABaseCharacter* UDetectionComponent::GetClosestCharacter()
{
	for (TActorIterator<ABaseCharacter> ItrCharacter(GetWorld()); ItrCharacter; ++ItrCharacter)
	{
		if (ItrCharacter->GetTeam() != ETeam::Enemy) // ugly
		{
			return *ItrCharacter;
		}
	}

	return nullptr;
}

void UDetectionComponent::EnableActiveDetection()
{
	bIsActiveDetectionEnabled = true;
}

void UDetectionComponent::DisableActiveDetection()
{
	bIsActiveDetectionEnabled = false;
}

void UDetectionComponent::RegisterDetectedCharacter(class ABaseCharacter* InCharacter)
{
	if (InCharacter)
	{
		if (DetectedCharacters.Contains(InCharacter) == false)
			DetectedCharacters.Add(InCharacter);
	}
}

void UDetectionComponent::UnregisterDetectedCharacter(class ABaseCharacter* InCharacter)
{
	if (InCharacter)
	{
		if (DetectedCharacters.Contains(InCharacter) == true)
			DetectedCharacters.Remove(InCharacter);
	}
}

bool UDetectionComponent::HasDetectedCharacter()
{
	if (DetectedCharacters.Num() != 0)
		return true;
	else
		return false;
}

void UDetectionComponent::Debug()
{
	ABaseCharacter* DebugCharacter = Cast<ABaseCharacter>(ParentActor);
	if (DebugCharacter)
	{
		if (DebugCharacter->GetTeam() == ETeam::Ally)
		{
			int i = 158;
			for (ABaseCharacter* DetectedCharacter : DetectedCharacters)
			{
				GEngine->AddOnScreenDebugMessage(i, 1.f, FColor::Red, FString::Printf(TEXT("Detected: %s"), *DetectedCharacter->GetName()));
				i++;
			}
		}
	}
}

/*if (GEngine) {

	//GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
	//GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Orange, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
	//GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Yellow, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));

}*/