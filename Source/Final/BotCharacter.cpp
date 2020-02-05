// Fill out your copyright notice in the Description page of Project Settings.


#include "BotCharacter.h"
#include "BotController.h"
#include "Animation/AnimInstance.h"

ABotCharacter::ABotCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ABotController::StaticClass();

//	GetFP_GunMesh()->SetOnlyOwnerSee(false);
//	GetFP_GunMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}


