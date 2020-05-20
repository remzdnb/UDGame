#include "Navigation/NavManager.h"
#include "Navigation/NavTile.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"

ANavManager::ANavManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANavManager::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ANavTile> NavTile(GetWorld()); NavTile; ++NavTile)
		TilesList.Add(*NavTile);
}

TArray<ANavTile*> ANavManager::GetSpawnTiles(uint8 TeamID)
{
	TArray<ANavTile*> FoundTiles;

	for (TActorIterator<ANavTile> NavTile(GetWorld()); NavTile; ++NavTile)
	{
		if (NavTile->GetIsSpawnLocation() && NavTile->GetTeamID() == TeamID)
			FoundTiles.Add(*NavTile);
	}

	return FoundTiles;
}

void ANavManager::ShowTilesInRange(FVector Origin, float Range)
{
	TArray<FHitResult> OutHits;

	//FVector SweepStart = GetActorLocation();
	//FVector SweepEnd = GetActorLocation();

	FlushPersistentDebugLines(GetWorld());
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(Range);
	DrawDebugSphere(GetWorld(), Origin, CollisionSphere.GetSphereRadius(), 50, FColor::Purple, true);

	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, Origin, FVector(Origin.X, Origin.Y, Origin.Z - 2.0f), FQuat::Identity, ECC_GameTraceChannel7, CollisionSphere);
		for (auto& Hit : OutHits)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("hit")));

			ANavTile* NavTile = Cast<ANavTile>(Hit.GetActor());
			if (NavTile)
				NavTile->Show();

			if (GEngine)
			{
				// screen log information on what was hit
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *Hit.Actor->GetName()));
				// uncommnet to see more info on sweeped actor
				// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("All Hit Information: %s"), *Hit.ToString()));
			}
		}
}

void ANavManager::HideTiles()
{
	FlushPersistentDebugLines(GetWorld());
	for (ANavTile* NavTile : TilesList)
	{
		NavTile->Hide();
	}
}
