// by Cookie Core


#include "AttackStartNotifyState.h"
#include "Engine.h"
#include "Final/Character/MainCharacter.h"


void UAttackiStartNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AMainCharacter* Player = Cast<AMainCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->AttackStart();
		}
	}
}

void UAttackiStartNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AMainCharacter* Player = Cast<AMainCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->AttackEnd();
		}
	}
}
