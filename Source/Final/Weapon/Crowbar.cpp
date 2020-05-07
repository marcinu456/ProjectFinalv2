// By Cookie Core


#include "Crowbar.h"
#include "Character/MainCharacter.h"

ACrowbar::ACrowbar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void ACrowbar::OnPickUp()
{
	//Load Animation Montage
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> MeleeFistAttackMontageObject(TEXT("AnimMontage'/Game/FightAnimation/Melee/Animations/MeleeFistAttackMontage.MeleeFistAttackMontage'"));
	//if (MeleeFistAttackMontageObject.Succeeded())
	//{
	//	//CharacterOwner->MeleeFistAttackMontage = MeleeFistAttackMontageObject.Object;
	//	UE_LOG(LogTemp, Warning, TEXT("It works here too"));
	//}
	CharacterOwner->MontageSectionIndex = 3;
	UE_LOG(LogTemp, Warning, TEXT("It works here too"));
	//Destroy();
}