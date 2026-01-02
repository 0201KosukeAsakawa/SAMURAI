// Copyright Epic Games, Inc. All Rights Reserved.

#include "SAMURAIGameMode.h"
#include "SAMURAICharacter.h"
#include "UObject/ConstructorHelpers.h"

ASAMURAIGameMode::ASAMURAIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
