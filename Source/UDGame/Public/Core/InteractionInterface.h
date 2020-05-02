#pragma once

#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class UDGAME_API IInteractionInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHoverStart();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHoverStop();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnLeftClick();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRightClick();
};
