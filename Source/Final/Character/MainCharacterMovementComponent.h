// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API UMainCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
protected:
	virtual void PostLoad() override;
	virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent)  override;



	UPROPERTY(Transient, DuplicateTransient)
	class	AMainCharacter* FinalCharacterOwner;
};
