// By Cookie Core

#include "Sword.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
ASword::ASword(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void ASword::OnPickUp()
{
	UE_LOG(LogTemp, Warning, TEXT("It works here too"));
	//Destroy();
}

