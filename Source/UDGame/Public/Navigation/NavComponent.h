#pragma once

#include "Components/ActorComponent.h"
#include "NavComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDGAME_API UNavComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UNavComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
