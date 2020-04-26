// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UDGameGameMode.h"
#include "UDGamePlayerController.h"
#include "UDGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUDGameGameMode::AUDGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUDGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}