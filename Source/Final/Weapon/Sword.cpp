// By Cookie Core

#include "Sword.h"
#include "Character/MainCharacter.h"
#include "Animation/AnimMontage.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"

ASword::ASword(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void ASword::OnPickUp()
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

