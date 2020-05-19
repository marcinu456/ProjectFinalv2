// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class AMainCharacter;
class UBoxComponent;
class USphereComponent;
class USkeletalMeshComponent;
class UCapsuleComponent;
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

public:
	virtual void OnPickUp() PURE_VIRTUAL(AWeapon::OnPickUp, );

	//UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = OnPickUp))
	//	void ReceiveOnPickUp(AMainCharacter* Player);

	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

	//
	void IsPickup();

	/*Create variable for CharacterOwner who get the weapon */
	UPROPERTY(Transient, DuplicateTransient)
		AMainCharacter* CharacterOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* WeaponMesh;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* BladeMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USphereComponent* SphereTriggerComponent;

	/* Set TimerDeley to activate AttackEnd Function, for each weapon use setup in blueprint*/
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TimerDelay = 0.7f;

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

	/* Inform if weapon is holding by Character*/
	bool bIsHolding = false;

	/* Handles input for start attack.*/
	UFUNCTION()
		void AttackStart();

	/* Handles input for end attack.*/
	UFUNCTION()
		void AttackEnd();

	/* Triggered when the collision hit event fires between weapon and enemy*/
	UFUNCTION()
		void OnAttackHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
