// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class AMainCharacter;
class UBoxComponent;
class USphereComponent;
class USkeletalMeshComponent;
class APlayerCharacter;
class AMainCharacter;

/*
Base class of weapon
*/


//TODO fix weapon localization
//TODO fix when player get second weapon
UCLASS(Abstract)
class FINAL_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	/* Sets default values for this actor's properties */
	AWeapon(const FObjectInitializer& ObjectInitializer);

	//UBoxComponent* GetSphereComponent() const { return CollisionComp; }
	//UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }
	//USphereComponent* GetSphereComponent() const { return SphereComponent; }

	/* Speed rotation of weapon*/
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		float RotationSpeed = 180.0f;
protected:
	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	//
	virtual void OnPickUp() PURE_VIRTUAL(AWeapon::OnPickUp, );

	//UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = OnPickUp))
	//	void ReceiveOnPickUp(AMainCharacter* Player);
public:	
	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

	//
	void IsPickup();

	/*Create variable for CharacterOwner who get the weapon */
	UPROPERTY(Transient, DuplicateTransient)
		AMainCharacter* CharacterOwner;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USphereComponent* SphereTriggerComponent;

public:
	/* Set the Character Owner who pickup the weapon*/
	void SetCharacterOwner(AMainCharacter* NewOwner);

	/* Attach weapon to Socket in CharacterOwner Mesh */
	void AttachToCharacter();
	/* Attach weapon from Socket in CharacterOwner Mesh */
	void DetachFromCharacter();

	/* Called when Character try Equip Weapon*/
	void OnEquip();

	/* Called when Character try UnEquip Weapon*/
	void OnUnEquip();

protected:

	/* Inform if weapon is holding by Character*/
	bool bIsHolding = false;
};
