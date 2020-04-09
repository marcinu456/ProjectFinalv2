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

/*
Klasa bazowa broni
*/

UCLASS(Abstract)
class FINAL_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon(const FObjectInitializer& ObjectInitializer);

	//UBoxComponent* GetSphereComponent() const { return CollisionComp; }
	//UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }
	//USphereComponent* GetSphereComponent() const { return SphereComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationSpeed = 180.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void OnPickUp() PURE_VIRTUAL(AWeapon::OnPickUp, );

	//UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = OnPickUp))
	//	void ReceiveOnPickUp(AMainCharacter* Player);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Funkcja wywowy³ana po stronie gracza
	void IsPickup();

	UPROPERTY(Transient, DuplicateTransient)
		APlayerCharacter* PlayerCharacterOwner;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USphereComponent* SphereTriggerComponent;

public:
	void SetOwningPawn(APlayerCharacter* NewOwner);

	void AttachToPlayer();
	void DetachFromPlayer();

	void OnEquip();
	void OnUnEquip();

protected:
	APlayerCharacter* MyPawn;
};
