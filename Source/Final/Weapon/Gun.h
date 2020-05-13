// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API AGun : public AWeapon
{
	GENERATED_BODY()
		AGun(const FObjectInitializer& ObjectInitializer);
protected:
	UFUNCTION(BlueprintCallable)
		virtual void OnPickUp() override;
};
