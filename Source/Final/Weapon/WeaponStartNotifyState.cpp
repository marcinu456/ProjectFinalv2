// By Cookie Core


#include "WeaponStartNotifyState.h"
#include "Engine.h"
#include "Weapon/Weapon.h"

void UWeaponStartNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AWeapon* Weapon = Cast<AWeapon>(MeshComp->GetOwner());
		if (Weapon != NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, __FUNCTION__);
			Weapon->AttackStart();
		}
	}
}

void UWeaponStartNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AWeapon* Weapon = Cast<AWeapon>(MeshComp->GetOwner());
		if (Weapon != NULL)
		{
			Weapon->AttackEnd();
		}
	}
}
