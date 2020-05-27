// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFinalGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API AMyFinalGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		virtual void StartPlay() override;

public:
	float killcount = 0;
	void HowManytoKill();
};
