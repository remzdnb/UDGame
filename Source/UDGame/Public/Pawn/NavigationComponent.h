#pragma once

#include "Components/ActorComponent.h"
#include "NavigationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UDGAME_API UNavigationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UNavigationComponent();

	void Init(AActor* InParentActor, class ANavBlock* SpawnBlock);

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegisterToNavBlock(class ANavBlock* TargetNavBlock);
	void UnregisterFromNavBlock();
	void SetIsInPosition(bool bNewIsInPosition);

	FORCEINLINE class ANavBlock* GetTargetNavBlock() const { return TargetNavBlock; }
	FORCEINLINE bool GetIsInPosition() const { return bIsInPosition; }

private:

	UPROPERTY(Transient) AActor* ParentActor;
	UPROPERTY(Transient) class ANavBlock* TargetNavBlock;

	bool bIsInPosition;
	float Size;
	uint32 MoveStepsLeft;
};
