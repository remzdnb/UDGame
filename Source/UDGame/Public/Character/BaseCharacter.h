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
	FString CharacterName;

	UPROPERTY()
	uint8 TeamID;

	//UPROPERTY()

private:

	class ABaseAIController* AIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* GroundWidgetComponent;
};

