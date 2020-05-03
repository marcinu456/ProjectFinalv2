// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Weapon/Weapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Vector.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "Final_CharacterMovementComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UFinal_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{

	//Load Animation Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MeleeFistAttackMontageObject(TEXT("AnimMontage'/Game/FightAnimation/Melee/Animations/MeleeFistAttackMontage.MeleeFistAttackMontage'"));
	if (MeleeFistAttackMontageObject.Succeeded())
	{
		MeleeFistAttackMontage = MeleeFistAttackMontageObject.Object;
	}

	LeftFistCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftFistCollisionBox"));
	LeftFistCollisionBox->SetupAttachment(RootComponent);
	LeftFistCollisionBox->SetCollisionProfileName("NoCollision");
	LeftFistCollisionBox->SetNotifyRigidBodyCollision(false);


	RightFistCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightFistCollisionBox"));
	RightFistCollisionBox->SetupAttachment(RootComponent);
	RightFistCollisionBox->SetCollisionProfileName("NoCollision");
	RightFistCollisionBox->SetNotifyRigidBodyCollision(false);


}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using MainaCharacter"));
	}
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->bShowMouseCursor = true;
		//PC->DefaultMouseCursor = EMouseCursor::Crosshairs;
	}

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	LeftFistCollisionBox->AttachToComponent(GetMesh(), AttachmentRules, "fist_l_collision");
	LeftFistCollisionBox->OnComponentHit.AddDynamic(this, &AMainCharacter::OnAttackHit);
	//LeftFistCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnAttackOverlapBegin);
	//LeftFistCollisionBox->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnAttackOverlapEnd);


	RightFistCollisionBox->AttachToComponent(GetMesh(), AttachmentRules, "fist_r_collision");
	RightFistCollisionBox->OnComponentHit.AddDynamic(this, &AMainCharacter::OnAttackHit);
	//RightFistCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnAttackOverlapBegin);
	//RightFistCollisionBox->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnAttackOverlapEnd);

}

// Called every frame 
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMainCharacter::AttackStart()
{
	Log(ELogLevel::INFO, __FUNCTION__);
	LeftFistCollisionBox->SetCollisionProfileName("Weapon");
	LeftFistCollisionBox->SetNotifyRigidBodyCollision(true);
	LeftFistCollisionBox->SetGenerateOverlapEvents(true);


	RightFistCollisionBox->SetCollisionProfileName("Weapon");
	RightFistCollisionBox->SetNotifyRigidBodyCollision(true);
	RightFistCollisionBox->SetGenerateOverlapEvents(true);
}


void AMainCharacter::AttackEnd()
{
	Log(ELogLevel::INFO, __FUNCTION__);
	LeftFistCollisionBox->SetCollisionProfileName("NoCollision");
	LeftFistCollisionBox->SetNotifyRigidBodyCollision(false);
	LeftFistCollisionBox->SetGenerateOverlapEvents(false);

	RightFistCollisionBox->SetCollisionProfileName("NoCollision");
	RightFistCollisionBox->SetNotifyRigidBodyCollision(false);
	RightFistCollisionBox->SetGenerateOverlapEvents(false);
}


void AMainCharacter::OnAttackHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Log(ELogLevel::WARNING, Hit.GetActor()->GetName());
}



/* declare overlap begin function */
void AMainCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->GetClass()->IsChildOf(AWeapon::StaticClass())&&bIsHoldingWeapon==false)
	{
		CurrentWeapon = Cast<AWeapon>(OtherActor);
	}
}

/* declare overlap end function */
void AMainCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp && bIsHoldingWeapon == false)
	{
		CurrentWeapon = NULL;
	}
}


void AMainCharacter::Log(ELogLevel LogLevel, FString Message)
{
	Log(LogLevel, Message, ELogOutput::ALL);
}

void AMainCharacter::Log(ELogLevel LogLevel, FString Message, ELogOutput LogOutput)
{
	// only print when screen is selected and the GEngine object is available
	if ((LogOutput == ELogOutput::ALL || LogOutput == ELogOutput::SCREEN) && GEngine)
	{
		// default color
		FColor LogColor = FColor::Cyan;
		// flip the color based on the type
		switch (LogLevel)
		{
		case ELogLevel::TRACE:
			LogColor = FColor::Green;
			break;
		case ELogLevel::DEBUG:
			LogColor = FColor::Cyan;
			break;
		case ELogLevel::INFO:
			LogColor = FColor::White;
			break;
		case ELogLevel::WARNING:
			LogColor = FColor::Yellow;
			break;
		case ELogLevel::ERROR:
			LogColor = FColor::Red;
			break;
		default:
			break;
		}
		// print the message and leave it on screen ( 4.5f controls the duration )
		GEngine->AddOnScreenDebugMessage(-1, 4.5f, LogColor, Message);
	}

	if (LogOutput == ELogOutput::ALL || LogOutput == ELogOutput::OUTPUT_LOG)
	{
		// flip the message type based on error level
		switch (LogLevel)
		{
		case ELogLevel::TRACE:
			UE_LOG(LogTemp, VeryVerbose, TEXT("%s"), *Message);
			break;
		case ELogLevel::DEBUG:
			UE_LOG(LogTemp, Verbose, TEXT("%s"), *Message);
			break;
		case ELogLevel::INFO:
			UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
			break;
		case ELogLevel::WARNING:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
			break;
		case ELogLevel::ERROR:
			UE_LOG(LogTemp, Error, TEXT("%s"), *Message);
			break;
		default:
			UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
			break;
		}
	}
}