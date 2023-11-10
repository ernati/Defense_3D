// Copyright Epic Games, Inc. All Rights Reserved.

#include "Defence_3DGameMode.h"
#include "Defence_3DCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADefence_3DGameMode::ADefence_3DGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
