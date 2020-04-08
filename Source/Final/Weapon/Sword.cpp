// By Cookie Core


#include "Sword.h"

void ASword::OnPickUp()
{
	UE_LOG(LogTemp, Warning, TEXT("It works here too"));
	Destroy();
}