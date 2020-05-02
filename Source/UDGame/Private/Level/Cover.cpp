#include "Level/Cover.h"
#include "Level/NavBlock.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"

ACover::ACover()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionProfileName("IgnoreAll");
	CollisionBox->SetupAttachment(RootScene);

	CoverParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("CoverParticle"));
	CoverParticle->SetupAttachment(RootScene);

	DirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	DirectionArrow->SetupAttachment(RootScene);

	PrimaryActorTick.bCanEverTick = false;
}

void ACover::BeginPlay()
{
	Super::BeginPlay();
	
	SelfRegisterToNavBlock();
}

void ACover::SelfRegisterToNavBlock()
{
	TArray<FHitResult> OutHits;

	FVector SweepStart = GetActorLocation();
	FVector Arrow = SweepStart + DirectionArrow->GetForwardVector() * 60;
	FVector SweepEnd = FVector(Arrow.X, Arrow.Y, Arrow.Z - 250.0f);

	//DrawDebugLine(GetWorld(), SweepStart, SweepEnd, FColor::Red, true, 50.0f);

	bool isHit = GetWorld()->LineTraceMultiByChannel(OutHits, SweepStart, SweepEnd, ECC_GameTraceChannel2);
	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			ANavBlock* NavBlock = Cast<ANavBlock>(Hit.GetActor());
			if (NavBlock)
			{
				NavBlock->RegisterCover(this);
				return;
			}

			if (GEngine)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *Hit.Actor->GetName()));
				// uncommnet to see more info on sweeped actor
				// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("All Hit Information: %s"), *Hit.ToString()));
			}
		}
	}
}

void ACover::OnHoverStart_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("hov start"));
}

void ACover::OnHoverStop_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TEXT("hov stop"));
}

void ACover::OnLeftClick_Implementation()
{
}

void ACover::OnRightClick_Implementation()
{
}

