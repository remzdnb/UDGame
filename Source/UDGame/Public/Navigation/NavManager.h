#pragma once

#include "GameFramework/Actor.h"
#include "NavManager.generated.h"

UCLASS()
class UDGAME_API ANavManager : public AActor
{
	GENERATED_BODY()
	
public:	

	ANavManager();

	virtual void BeginPlay() override;

	TArray<class ANavTile*> GetSpawnTiles(uint8 TeamID);

	void ShowTilesInRange(FVector Origin, float Range);
	void HideTiles();

private:

	UPROPERTY(Transient) TArray<class ANavTile*> TilesList;
};
