#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Blueprintable)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABaseCharacter();

	//void Init(FName TableRowName, uint8 NewTeamID, bool bNewIsPlayerControlled);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:

	class ABaseAIController* AIController;

};

