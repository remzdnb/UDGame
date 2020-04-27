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

	void Init(FName TableRowName, uint8 NewTeamID);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	uint8 TeamID;

private:

	class ABaseAIController* AIController;

};

