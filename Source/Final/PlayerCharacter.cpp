// By Cookie Core


#include "PlayerCharacter.h"
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
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-90.f, 0.f, 0.f); //Camera Rotation
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

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetCursorDirectory();
	//PickUpWeapon(bIsPickUp);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Attack bindigs
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::AttackInput);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AMainCharacter::AttackEnd);

	//Pickup binding
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &APlayerCharacter::PickUp);
}

void APlayerCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	//AddMovementInput(Direction, Value);
	// Use World direction.
	FVector Direction = FVector::ForwardVector;
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	//AddMovementInput(Direction, Value);
	// Use World direction.
	FVector Direction = FVector::RightVector;
	AddMovementInput(Direction, Value);

}

void APlayerCharacter::AttackInput()
{

	//generate random number between 1 and 2
	int MontageSectionIndex = rand() % 2 + 1;

	// fstring animation section
	FString MontageSection = "Start_" + FString::FromInt(MontageSectionIndex);

	PlayAnimMontage(MeleeFistAttackMontage, 1.f, FName(*MontageSection));
}

void APlayerCharacter::PickUp()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->IsPickup();
	}
}


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

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->GetClass()->IsChildOf(AWeapon::StaticClass()))
	{
		CurrentWeapon = Cast<AWeapon>(OtherActor);
	}
}

void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		CurrentWeapon = NULL;
	}
}
