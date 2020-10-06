// By Cookie Core


#include "MainCharacterMovementComponent.h"
#include "Final/Character/MainCharacter.h"

void UMainCharacterMovementComponent::PostLoad()
{
	Super::PostLoad();

	// Cache owner. Cast is slow so we want to do it once after load.
	FinalCharacterOwner = Cast<AMainCharacter>(PawnOwner);
}

void UMainCharacterMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
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