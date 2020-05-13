// By Cookie Core


#include "Gun.h"
#include "Character/MainCharacter.h"

AGun::AGun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void AGun::OnPickUp()
{
	CharacterOwner->MontageSectionIndex = 3;
	UE_LOG(LogTemp, Warning, TEXT("It works here too"));
}
