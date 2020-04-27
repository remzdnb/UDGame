#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UDCharacter.generated.h"

UCLASS(Blueprintable)
class AUDCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AUDCharacter();

	//void Init(FName TableRowName, uint8 NewTeamID, bool bNewIsPlayerControlled);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:

	class ABaseAIController* AIController;

};

