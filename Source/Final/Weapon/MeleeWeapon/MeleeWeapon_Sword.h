// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "Weapon/MeleeWeapon/MeleeWeapon.h"
#include "MeleeWeapon_Sword.generated.h"

/**
 * 
 */
UCLASS()
class FINAL_API AMeleeWeapon_Sword : public AMeleeWeapon
{
	GENERATED_BODY()
		AMeleeWeapon_Sword(const FObjectInitializer& ObjectInitializer);
protected:
	UFUNCTION(BlueprintCallable)
		virtual void OnPickUp() override;
};
