// Fill out your copyright notice in the Description page of Project Settings.


#include "Final_CharacterMovementComponent.h"
#include "MainCharacter.h"

void UFinal_CharacterMovementComponent::PostLoad()
{
	Super::PostLoad();

	// Cache owner. Cast is slow so we want to do it once after load.
	FinalCharacterOwner = Cast<AMainCharacter>(PawnOwner);
}

void UFinal_CharacterMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
	if (NewUpdatedComponent)
	{
		const ACharacter* NewCharacterOwner = Cast<AMainCharacter>(NewUpdatedComponent->GetOwner());
		if (NewCharacterOwner == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("%s owned by %s must update a  component owned by a programowaniegierCharacter"), *GetName(), *GetNameSafe(NewUpdatedComponent->GetOwner()));
			return;
		}
	}

	Super::SetUpdatedComponent(NewUpdatedComponent);

	FinalCharacterOwner = Cast<AMainCharacter>(PawnOwner);
}


