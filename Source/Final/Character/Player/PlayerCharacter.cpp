// By Cookie Core


#include "PlayerCharacter.h"
#include "Weapon/Weapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Vector.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);
	

	// bind trigger events
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);

	CurrentWeapon = NULL;

	HoldingWeapon = NULL;
}

/* Called every frame */
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetCursorDirectory();
	//PickUpWeapon(bIsPickUp);
}

/* Called to bind functionality to input */
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Attack bindings
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::AttackInput);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AMainCharacter::AttackEnd);

	//Pickup binding
	PlayerInputComponent->BindAction("PickUpWeapon", IE_Pressed, this, &APlayerCharacter::PickUpWeapon);
}

/* Handles input for moving forward and backward. */
void APlayerCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	//AddMovementInput(Direction, Value);
	// Use World direction.
	FVector Direction = FVector::ForwardVector;
	AddMovementInput(Direction, Value);
}

/* Handles input for moving right and left.*/
void APlayerCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	//AddMovementInput(Direction, Value);
	// Use World direction.
	FVector Direction = FVector::RightVector;
	AddMovementInput(Direction, Value);

}

/* Trigger attack anim based on user input */
void APlayerCharacter::AttackInput()
{

	//generate random number between 1 and 2
	if(bIsHoldingWeapon==false)
	{
		MontageSectionIndex = rand() % 2 + 1;
	}
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
	// fstring animation section
	FString MontageSection = "Start_" + FString::FromInt(MontageSectionIndex);

	PlayAnimMontage(MeleeFistAttackMontage, 1.f, FName(*MontageSection));
}

/* Called when Player using PickUpWeapon Action Mapping Input*/
void APlayerCharacter::PickUpWeapon()
{
	//AWeapon* Spawner = GetWorld()->SpawnActor<AWeapon>(WeaponSpawn);
	if (CurrentWeapon && bIsHoldingWeapon == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter::PickUpWeapon()"));
		bIsHoldingWeapon = true;
		CurrentWeapon->SetCharacterOwner(this);
		//Spawner->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, "Weapon_socket" );
		CurrentWeapon->IsPickup();
		CurrentWeapon->OnEquip();
	}
	else if (CurrentWeapon && bIsHoldingWeapon == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("YupYup"));
		CurrentWeapon->OnUnEquip();
		bIsHoldingWeapon = false;
	}
}

/*Rotate Player to Cursor Position*/
void APlayerCharacter::SetCursorDirectory()
{

	FVector CurrLoc = this->GetActorLocation();
	FHitResult hitResult;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, hitResult);
	FVector hitLoc = hitResult.Location;
	FRotator newRot = this->GetActorRotation();
	float newYaw = (hitLoc - CurrLoc).Rotation().Yaw;;
	newRot.Yaw = newYaw;
	this->GetController()->SetControlRotation(newRot);
}

