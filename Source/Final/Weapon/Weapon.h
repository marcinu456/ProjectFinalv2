// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class AMainCharacter;
class USphereComponent;
class UStaticMeshComponent;
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
	AWeapon();

	USphereComponent* GetSphereComponent() const { return SphereComponent; }
	UStaticMeshComponent* GetMeshComponent() const { return MeshComponent; }

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
		USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MeshComponent;
};
