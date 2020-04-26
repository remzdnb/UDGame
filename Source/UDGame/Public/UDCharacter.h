// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

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

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

private:

};

