// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "BotCharacter.generated.h"


class UBehaviorTree;
/**
 * 
 */
UCLASS()
class FINAL_API ABotCharacter : public AMainCharacter
{
	GENERATED_BODY()
public:
	ABotCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = Behavior)
		UBehaviorTree* BotBehavior;
};
