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
		DetectVisibleCharacters();
}

void UDetectionComponent::DetectVisibleCharacters()
{
	DetectedCharacters.Empty();
	TArray<class ABaseCharacter*> NewDetectedCharacters;

	for (TActorIterator<ABaseCharacter> ItrCharacter(GetWorld()); ItrCharacter; ++ItrCharacter) // Update
	{
		if (ItrCharacter->GetIsDead() == false && ItrCharacter->Team == ETeam::Enemy)
		{
			FHitResult OutHit;
			FCollisionQueryParams CollisionParams;
			FVector Start = FVector(ParentActor->GetActorLocation().X, ParentActor->GetActorLocation().Y, ItrCharacter->GetActorLocation().Z + 50.0f);
			FVector End = FVector(ItrCharacter->GetActorLocation().X, ItrCharacter->GetActorLocation().Y, ItrCharacter->GetActorLocation().Z + 50.0f);

			if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel1, CollisionParams))
			{
				if (OutHit.bBlockingHit)
				{
					DrawDebugLine(GetWorld(), Start, OutHit.Location, FColor::Green, false, 0.1f, 0, 1);

					ABaseCharacter* CurrentCharacter = Cast<ABaseCharacter>(OutHit.GetActor());
					if (CurrentCharacter)
					{
						NewDetectedCharacters.Add(CurrentCharacter);
						DetectedCharacters.Add(CurrentCharacter);
					}


					if (GEngine) {

						//GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
						//GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Orange, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
						//GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Yellow, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));

					}
				}
			}
		}
	}

	for (ABaseCharacter* NewDetectedCharacter : NewDetectedCharacters) // update enemy detection
	{
		if (DetectedCharacters.Contains(NewDetectedCharacter) == false)
		{

		}

	}
}

ABaseCharacter* UDetectionComponent::GetClosestDetectedCharacter()
{
	if (ParentActor)
	{
		float MinDistance = 9999999.9f;
		ABaseCharacter* CharacterRef = nullptr;

		for (ABaseCharacter* CurrentCharacter : DetectedCharacters)
		{
			if (FVector::Dist(ParentActor->GetActorLocation(), CurrentCharacter->GetActorLocation()) < MinDistance)
			{
				CharacterRef = CurrentCharacter;
				MinDistance = FVector::Dist(ParentActor->GetActorLocation(), CurrentCharacter->GetActorLocation());
			}
		}

		return CharacterRef;
	}

	return nullptr;
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
