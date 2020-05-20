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

	virtual void OnHoverStart() = 0;
	virtual void OnHoverStop() = 0;
	virtual void OnSelectionStart() = 0;
	virtual void OnSelectionStop() = 0;
};
