#pragma once

#include "UDGameTypes.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

UCLASS()
class UDGAME_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABaseAIController();

	virtual void BeginPlay() override;

	FORCEINLINE AActor* GetTargetCharacter() const { return TargetActor; }

protected:

	UPROPERTY(Transient) AActor* TargetActor;

	// del

public:

	void MovePossessedCharacter(FVector TargetLocation);

protected:

	bool bIsMoving;
	FVector TargetLocation;

};
