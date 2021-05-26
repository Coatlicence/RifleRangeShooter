// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RifleRangeShooterGameMode.h"
#include "RifleRangeShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARifleRangeShooterGameMode::ARifleRangeShooterGameMode() : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
