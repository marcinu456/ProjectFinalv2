// By Cookie Core


#include "MeleeWeapon.h"
#include "Character/MainCharacter.h"
#include "Character/MainCharacter.h"
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

    Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,
        TEXT("Mesh"));
    RootComponent = Mesh;

    ProxBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this,
        TEXT("ProxBox"));
    ProxBox->OnComponentBeginOverlap.AddDynamic(this,
        &AMeleeWeapon::Prox);
    ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

    SphereTriggerComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereTriggerComponent"));
    SphereTriggerComponent->InitSphereRadius(100.0f);
    SphereTriggerComponent->SetCollisionProfileName(TEXT("Trigger"));
    SphereTriggerComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	
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