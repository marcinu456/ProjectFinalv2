// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Sword.generated.h"

class USphereComponent;
class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class FINAL_API ASword : public AWeapon
{
	GENERATED_BODY()
	
protected:
	virtual void OnPickUp(AMainCharacter* Player) override;
};
