#pragma once

#include "CoreMinimal.h"
#include "Character/BaseAIController.h"
#include "AllyAIController.generated.h"

UCLASS()
class UDGAME_API AAllyAIController : public ABaseAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	void UpdateDetectedCharacters();
};
