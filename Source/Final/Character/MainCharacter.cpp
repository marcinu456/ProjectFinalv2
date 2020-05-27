// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Weapon/Weapon.h"
#include "Weapon/MeleeWeapon/MeleeWeapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Vector.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "Final_CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "MyFinalGameModeBase.h"

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

	AMyFinalGameModeBase* GameMode = Cast<AMyFinalGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->killcount += 1;
}

// Called every frame 
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMainCharacter::AttackStart()
{
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
	LeftFistCollisionBox->SetCollisionProfileName("Weapon");
	LeftFistCollisionBox->SetNotifyRigidBodyCollision(true);
	LeftFistCollisionBox->SetGenerateOverlapEvents(true);


	RightFistCollisionBox->SetCollisionProfileName("Weapon");
	RightFistCollisionBox->SetNotifyRigidBodyCollision(true);
	RightFistCollisionBox->SetGenerateOverlapEvents(true);
}


void AMainCharacter::AttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
	LeftFistCollisionBox->SetCollisionProfileName("NoCollision");
	LeftFistCollisionBox->SetNotifyRigidBodyCollision(false);
	LeftFistCollisionBox->SetGenerateOverlapEvents(false);

	RightFistCollisionBox->SetCollisionProfileName("NoCollision");
	RightFistCollisionBox->SetNotifyRigidBodyCollision(false);
	RightFistCollisionBox->SetGenerateOverlapEvents(false);
}


void AMainCharacter::OnAttackHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit name: %s"), *(Hit.GetActor()->GetName()));
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

float AMainCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Oj jak boli"));
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (DamageAmount > 0.f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("[Jeb]"));
		Health -= DamageAmount;
	}
	if(Health<=0.f)
	{
		// Stop movement.
		GetMovementComponent()->StopMovementImmediately();
		// Disable OnTick for component - optimization.
		GetMovementComponent()->SetComponentTickEnabled(false);

		// Turn on physics = here enable radgoll for mesh.
		GetMesh()->SetSimulatePhysics(true);
		// and set proper collision profile.
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		// Disable collision for capsule.
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AMyFinalGameModeBase* GameMode = Cast<AMyFinalGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->killcount -= 1;
		GameMode->HowManytoKill();
	}
	return AActor::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AMainCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// instantiate the melee weapon if a bp was selected 
	if (BP_MeleeWeapon)
	{
		MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(
			BP_MeleeWeapon, FVector(), FRotator());

		if (MeleeWeapon)
		{
			const USkeletalMeshSocket* socket = GetMesh()->GetSocketByName(
				FName("Weapon_socket")); // be sure to use correct 
									// socket name! 
			socket->AttachActor(MeleeWeapon, GetMesh());
			MeleeWeapon->WeaponHolder = this;
		}
	}
}