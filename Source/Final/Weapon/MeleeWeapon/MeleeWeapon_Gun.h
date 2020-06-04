// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "MeleeWeapon.h"
#include "MeleeWeapon_Gun.generated.h"

/**
 *
 */
UCLASS()
class FINAL_API AMeleeWeapon_Gun : public AMeleeWeapon
{
	GENERATED_BODY()
		AMeleeWeapon_Gun(const FObjectInitializer& ObjectInitializer);
protected:
	UFUNCTION(BlueprintCallable)
		virtual void OnPickUp() override;
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> ProjectileClass;

	void OnFire();
};
