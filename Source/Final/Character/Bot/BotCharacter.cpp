// Cookie Core



#include "BotCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BotController.h"
#include "Final/Weapon/MeleeWeapon/MeleeWeapon.h"
#include "Math/Vector.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Final/Character/Player/PlayerCharacter.h"

ABotCharacter::ABotCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ABotController::StaticClass();

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);


	// bind trigger events
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABotCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &ABotCharacter::OnOverlapEnd);
	//	GetFP_GunMesh()->SetOnlyOwnerSee(false);
	//	GetFP_GunMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));


    Speed = 10;
    HitPoints = 20;
    Experience = 0;
    BPLoot = NULL;
    BaseAttackDamage = 1;
    AttackTimeout = 1.5f;
    TimeSinceLastStrike = 0;

    SightSphere = CreateDefaultSubobject<USphereComponent>("SightSphere");
    SightSphere->SetupAttachment(RootComponent);
   // SightSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

    AttackRangeSphere = CreateDefaultSubobject<USphereComponent>("AttackRangeSphere");
    AttackRangeSphere->SetupAttachment(RootComponent);
   //AttackRangeSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

}


void ABotCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    APlayerCharacter* avatar = Cast<APlayerCharacter>(
        UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (!avatar) return;
    FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
    float distanceToPlayer = toPlayer.Size();
    // If the player is not in the SightSphere of the monster, 
    // go back 
    if (distanceToPlayer > SightSphere->GetScaledSphereRadius())
    {
        // If the player is out of sight, 
        // then the enemy cannot chase 
        return;
    }

    toPlayer /= distanceToPlayer;  // normalizes the vector 
    // Actually move the monster towards the player a bit 
    AddMovementInput(toPlayer, Speed * DeltaTime);
    toPlayer.Normalize(); // reduce to unit vector 
                        // Actually move the monster towards the player a bit
    AddMovementInput(toPlayer, Speed * DeltaTime); // At least face the target
    // Gets you the rotator to turn something // that looks in the `toPlayer`direction 
    FRotator toPlayerRotation = toPlayer.Rotation();
    toPlayerRotation.Pitch = 0; // 0 off the pitch
    RootComponent->SetWorldRotation(toPlayerRotation);
}

void ABotCharacter::AtackMeleeWeapon()
{
	if(CurrentWeapon)
    CurrentWeapon->AttackStart();
}



//void ABotCharacter::PickUpWeapon()
//{
//	//TODO write pickup weapon by bot
//	UE_LOG(LogTemp, Warning, TEXT("ABotCharacter::PickUpWeapon()"));
//
//	if (CurrentWeapon)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Have CurrentWeapon"));
//	}
//	else 
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Not CurrentWeapon"));
//	}
//	if (CurrentWeapon && bIsHoldingWeapon == false)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("ABotCharacter::PickUpWeapon()"));
//		bIsHoldingWeapon = true;
//		CurrentWeapon->SetCharacterOwner(this);
//		//Spawner->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, "Weapon_socket" );
//		CurrentWeapon->IsPickup();
//		CurrentWeapon->OnEquip();
//
//	}
//	else if (CurrentWeapon && bIsHoldingWeapon == true)
//	{
//		bIsHoldingWeapon = false;
//		UE_LOG(LogTemp, Warning, TEXT("Yup"));
//		CurrentWeapon->OnUnEquip();
//	}
//}