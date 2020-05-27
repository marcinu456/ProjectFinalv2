// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MainCharacter.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

class AWeapon;

UCLASS()
class FINAL_API APlayerCharacter : public AMainCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

	/* Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/* Handles input for moving forward and backward. */
	UFUNCTION()
		void MoveForward(float Value);

	/* Handles input for moving right and left.*/
	UFUNCTION()
		void MoveRight(float Value);

	/* Trigger attack anim based on user input */
	void AttackInput();

	/* Called when Player using PickUpWeapon Action Mapping Input*/
	void PickUpWeapon();

	/*Rotate Player to Cursor Position*/
	void SetCursorDirectory();

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Holding Component */
	UPROPERTY(EditAnywhere)
		class USceneComponent* HoldingComponent;

	/* Create Trigger Capsule to get weapon*/
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		class UCapsuleComponent* TriggerCapsule;


	
private:
	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	void ResetLevel();

};
