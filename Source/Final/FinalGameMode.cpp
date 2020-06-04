// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FinalGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

//AFinalGameMode::AFinalGameMode()
//{
//	// use our custom PlayerController class
//	PlayerControllerClass = AFinalPlayerController::StaticClass();
//
//	// set default pawn class to our Blueprinted character
//	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
//	if (PlayerPawnBPClass.Class != NULL)
//	{
//		DefaultPawnClass = PlayerPawnBPClass.Class;
//	}
//
//	
//}

void AFinalGameMode::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		// Display a debug message for five seconds. 
		// The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is TopDown"));
	}
	HowManytoKill();
}

void AFinalGameMode::HowManytoKill()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("kill %f"), killcount - 1));
	if((killcount-1)==0)
	GetWorld()->ServerTravel(FString("World'/Game/BluePrint_MainFolder/Maps/MainMenu.MainMenu'"));
}