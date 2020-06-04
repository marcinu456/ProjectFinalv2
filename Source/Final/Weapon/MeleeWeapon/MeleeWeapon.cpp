// By Cookie Core


#include "MeleeWeapon.h"
#include "Final/Character/MainCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

AMeleeWeapon::AMeleeWeapon(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    AttackDamage = 50;
    Swinging = false;
    WeaponHolder = NULL;

    Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
    Mesh->SetCollisionProfileName(TEXT("NoCollision"));
    RootComponent = Mesh;

    ProxBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
    ProxBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::Prox);
    ProxBox->SetupAttachment(RootComponent);
   // ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform); Powoduje b³¹d przy pakowaniu

    SphereTriggerComponent = CreateDefaultSubobject<USphereComponent>("SphereTriggerComponent");
    SphereTriggerComponent->InitSphereRadius(100.0f);
    SphereTriggerComponent->SetCollisionProfileName(TEXT("Trigger"));
	SphereTriggerComponent->SetupAttachment(RootComponent);
   // SphereTriggerComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform); Powoduje b³¹d przy pakowaniu

}

int AMeleeWeapon::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // don't hit non root components 
    if (OtherComp != OtherActor->GetRootComponent())
    {
        return -1;
    }

    // avoid hitting things while sword isn't swinging, 
    // avoid hitting yourself, and 
    // avoid hitting the same OtherActor twice 
    if (Swinging && OtherActor != (AActor*)WeaponHolder &&
        !ThingsHit.Contains(OtherActor))
    {
        OtherActor->TakeDamage(AttackDamage, FDamageEvent(), NULL, this);
        ThingsHit.Add(OtherActor);
    }

    return 0;
}

void AMeleeWeapon::Swing()
{
    ThingsHit.Empty();  // empty the list 
    Swinging = true;
}

void AMeleeWeapon::Rest()
{
    ThingsHit.Empty();
    Swinging = false;
}

void AMeleeWeapon::AttackStart()
{
    //TODO Change this after fix animation and delete AttackisStart()
    //UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
    //BladeMesh->SetCollisionProfileName(TEXT("Projectile"));
    //BladeMesh->Activate();
    //BladeMesh->SetNotifyRigidBodyCollision(true);
    //BladeMesh->SetGenerateOverlapEvents(true);
    ThingsHit.Empty();  // empty the list 
    Swinging = true;
    FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMeleeWeapon::AttackEnd, TimerDelay, true, TimerDelay);
}



void AMeleeWeapon::AttackEnd()
{
    UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
    //BladeMesh->Deactivate();
    //BladeMesh->SetNotifyRigidBodyCollision(false);
    //BladeMesh->SetGenerateOverlapEvents(false);
    ThingsHit.Empty();
    Swinging = false;
    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}



void AMeleeWeapon::IsPickup()
{
    UE_LOG(LogTemp, Warning, TEXT("It works"));
    // Call virtual function from subclass - C++.
    OnPickUp();
}

/* Set the Character Owner who pickup the weapon*/
void AMeleeWeapon::SetCharacterOwner(AMainCharacter* NewOwner)
{
    if (WeaponHolder != NewOwner)
    {
        WeaponHolder = NewOwner;
    }
}

/* Attach weapon to Socket in CharacterOwner Mesh */
void AMeleeWeapon::AttachToCharacter()
{
    if (WeaponHolder)
    {
        UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
        UE_LOG(LogTemp, Warning, TEXT("Character name: %s"), *(WeaponHolder->GetName()));
        DetachFromCharacter();
        USkeletalMeshComponent* Character = WeaponHolder->GetMesh();
        Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        Mesh->SetHiddenInGame(false);
        Mesh->AttachTo(Character, "Weapon_socket");
        SphereTriggerComponent->SetCollisionProfileName(TEXT("HoldWeapon"));
    }
}

/* Attach weapon from Socket in CharacterOwner Mesh */
void AMeleeWeapon::DetachFromCharacter()
{
    Mesh->DetachFromParent();
    if (WeaponHolder)
    {

        SetActorLocation(WeaponHolder->GetActorLocation());
        Mesh->SetRelativeLocation(WeaponHolder->GetActorLocation());
        SphereTriggerComponent->SetCollisionProfileName(TEXT("Trigger"));
    }
}

/* Called when Character try Equip Weapon*/
void AMeleeWeapon::OnEquip()
{
    UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
    AttachToCharacter();
    bIsHolding = true;
}

/* Called when Character try UnEquip Weapon*/
void AMeleeWeapon::OnUnEquip()
{
    DetachFromCharacter();
    bIsHolding = false;
}