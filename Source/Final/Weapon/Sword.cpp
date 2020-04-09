// By Cookie Core

#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Sword.h"

ASword::ASword(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void ASword::OnPickUp()
{
	UE_LOG(LogTemp, Warning, TEXT("It works here too"));
	//Destroy();
}

