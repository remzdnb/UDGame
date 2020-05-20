#pragma once

#include "UDGameTypes.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDGAME_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCombatComponent();

	void Init(AActor* InParentActor, ETeam NewTeam);

	virtual void BeginPlay() override;

	FAttackResult GenerateAttackResult(); // static ?
	void ApplyAttack(FAttackResult AttackResult);

	FORCEINLINE ETeam GetTeam() const { return Team; }

private:

	UPROPERTY(Transient) class UBaseGameInstance* GInstance;
	UPROPERTY(Transient) AActor* ParentActor;

	class IPawnInterface* PawnInterface;
	ETeam Team;
};
