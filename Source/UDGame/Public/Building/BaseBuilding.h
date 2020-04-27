#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBuilding.generated.h"

UCLASS()
class UDGAME_API ABaseBuilding : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseBuilding();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	uint8 TeamID;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
};
