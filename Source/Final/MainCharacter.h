// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class ELogLevel : uint8 {
	TRACE			UMETA(DisplayName = "Trace"),
	DEBUG			UMETA(DisplayName = "Debug"),
	INFO			UMETA(DisplayName = "Info"),
	WARNING			UMETA(DisplayName = "Warning"),
	ERROR			UMETA(DisplayName = "Error")
};

UENUM(BlueprintType)
enum class ELogOutput : uint8 {
	ALL				UMETA(DisplayName = "All levels"),
	OUTPUT_LOG		UMETA(DisplayName = "Output log"),
	SCREEN			UMETA(DisplayName = "Screen")
};

UENUM(BlueprintType)
enum class EAttackType : uint8 {
	MELEE_FIST			UMETA(DisplayName = "Melee - Fist")
};


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

	//// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//// Handles input for moving forward and backward.
	//UFUNCTION()
	//	void MoveForward(float Value);

	//// Handles input for moving right and left.
	//UFUNCTION()
	//	void MoveRight(float Value);

	////Trigger attack anim based on user input
	//	void AttackInput();

	// Handles input for start attack.
		void AttackStart();
	
	// Handles input for end attack.
		void AttackEnd();

	// Triggered when the collision hit event fires between weapon and enemy
	UFUNCTION()
		void OnAttackHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//// Triggered when colider overlaps another component
	//UFUNCTION()
	//	void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//// Triggered when colider stops overlaps another component
	//UFUNCTION()
	//	void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		
	//	void SetCursorDirectory();

	///** Top down camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	class UCameraComponent* TopDownCameraComponent;

	///** Camera boom positioning the camera above the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	class USpringArmComponent* CameraBoom;

	//bool IsAttack;
		/** Melee fist attack montage */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* MeleeFistAttackMontage;

private:
	///** A decal that projects to the cursor location. */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	class UDecalComponent* CursorToWorld;


	/** LeftFistCollisionBox */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LeftFistCollisionBox;
	
	
	/** RightFistCollisionBox */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RightFistCollisionBox;
	/**
	* Log - prints a message to all the log outputs with a specific color
	* @param LogLevel {@see ELogLevel} affects color of log
	* @param FString the message for display
	*/
	void Log(ELogLevel LogLevel, FString Message);
	/**
	* Log - prints a message to all the log outputs with a specific color
	* @param LogLevel {@see ELogLevel} affects color of log
	* @param FString the message for display
	* @param ELogOutput - All, Output Log or Screen
	*/
	void Log(ELogLevel LogLevel, FString Message, ELogOutput LogOutput);

public:
	UPROPERTY(VisibleAnywhere, Category = Spawn)
		TSubclassOf<AWeapon> WeaponSpawn;

	AWeapon* CurrentWeapon;

};
