// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Crowbar.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API ACrowbar : public AWeapon
{
	GENERATED_BODY()
		ACrowbar(const FObjectInitializer& ObjectInitializer);
protected:
	UFUNCTION(BlueprintCallable)
		virtual void OnPickUp() override;
};
