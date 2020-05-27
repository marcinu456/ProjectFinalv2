// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.generated.h"

class AWeapon;


UCLASS(config = Game)
class FINAL_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Handles input for start attack.
		void AttackStart();
	
	// Handles input for end attack.
		void AttackEnd();

	// Triggered when the collision hit event fires between weapon and enemy
	UFUNCTION()
		void OnAttackHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//bool IsAttack;
		/** Melee fist attack montage */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* MeleeFistAttackMontage;

private:

	/** LeftFistCollisionBox */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LeftFistCollisionBox;
	
	
	/** RightFistCollisionBox */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RightFistCollisionBox;

public:
	UPROPERTY(VisibleAnywhere, Category = Spawn)
		TSubclassOf<AWeapon> WeaponSpawn;

	AWeapon* CurrentWeapon;

	AWeapon* HoldingWeapon;

	/* declare overlap begin function */
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/* declare overlap end function */
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/* Inform if Character holding weapon*/
	bool bIsHoldingWeapon = false;

	/* Set Number of AnimMontage*/
	int32 MontageSectionIndex = 0;//rand() % 2 + 1;
	
	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float Health = 100.0f;
};
