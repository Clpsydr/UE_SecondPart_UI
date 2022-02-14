// Copyright Epic Games, Inc. All Rights Reserved.

#include "distanceGameMode.h"
#include "distancePlayerController.h"
#include "distanceCharacter.h"
#include "UObject/ConstructorHelpers.h"

AdistanceGameMode::AdistanceGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AdistancePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// generating several creatures in the world?
	// need to bake in a level though
	// also needs spawn points and random spread around them
}