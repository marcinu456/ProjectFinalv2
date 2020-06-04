// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FinalGameMode.generated.h"

UCLASS(minimalapi)
class AFinalGameMode : public AGameModeBase
{
	GENERATED_BODY()
		virtual void StartPlay() override;
public:
	//AFinalGameMode();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyProperties)
		float killcount = 0;
	
	void HowManytoKill();
};



