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

	ASword(const FObjectInitializer& ObjectInitializer);
protected:
	UFUNCTION(BlueprintCallable)
	virtual void OnPickUp() override;

};
