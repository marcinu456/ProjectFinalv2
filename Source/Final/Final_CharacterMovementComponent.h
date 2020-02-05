// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Final_CharacterMovementComponent.generated.h"


class AMainCharacter;
/**
 * 
 */
UCLASS()
class FINAL_API UFinal_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
protected:
	virtual void PostLoad() override;
	virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent)  override;



	UPROPERTY(Transient, DuplicateTransient)
		AMainCharacter* FinalCharacterOwner;
};
