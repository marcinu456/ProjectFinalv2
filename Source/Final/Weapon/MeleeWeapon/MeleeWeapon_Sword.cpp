// By Cookie Core


#include "MeleeWeapon_Sword.h"
#include "Final/Character/MainCharacter.h"
#include "Animation/AnimMontage.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"

AMeleeWeapon_Sword::AMeleeWeapon_Sword(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void AMeleeWeapon_Sword::OnPickUp()
{
	//Load Animation Montage
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> MeleeFistAttackMontageObject(TEXT("AnimMontage'/Game/FightAnimation/Melee/Animations/MeleeFistAttackMontage.MeleeFistAttackMontage'"));
	//if (MeleeFistAttackMontageObject.Succeeded())
	//{
	//	//CharacterOwner->MeleeFistAttackMontage = MeleeFistAttackMontageObject.Object;
	//	UE_LOG(LogTemp, Warning, TEXT("It works here too"));
	//}
	WeaponHolder->MontageSectionIndex = 3;
	UE_LOG(LogTemp, Warning, TEXT("It works here too"));
	//Destroy();
}
