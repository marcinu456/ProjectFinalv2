// Cookie Core



#include "BotCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "BotController.h"
#include "Final/Weapon/MeleeWeapon/MeleeWeapon.h"
#include "Math/Vector.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "Animation/AnimInstance.h"

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