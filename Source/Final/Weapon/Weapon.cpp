// By Cookie Core

#include "MainCharacter.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Weapon.h"

// Sets default values
AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 1. Create components.
	/*	Use _CreateDefaultSubobject_ to create components in C++
		There are a few similar functions for advanced users:
			- CreateEditorOnlyDefaultSubobject
			- CreateOptionalDefaultSubobject
			- All of them are commented in code or in documentation
	*/
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("CollisionComp");
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SphereTriggerComponent = CreateDefaultSubobject<USphereComponent>("SphereTriggerComponent");
	// 2. Set default parameters.
	/*	You can set any parameters you can change in Blueprint and even more.
		Quite often you will need to call a function instead of setting the property directly.
	*/
	SphereTriggerComponent->InitSphereRadius(100.0f); //< Here you call InitSphereRadius, after the ctor you should call SetSphereRadius
	//SphereComponent->bNotifyRigidBodyCollision = true; //< Not needed. Simulation Generates Hit Events.
	//SphereComponent->SetGenerateOverlapEvents(true); //< Not needed.
	SphereTriggerComponent->SetCollisionProfileName(TEXT("Trigger"));

	// 3. Setup attachments.
	/*	Define RootComponet.
		SetupAttachment - attach child to parent - works only in ctor.
		@remarks If you want change hierarchy call AttachToComponent after the ctor.

	*/
	RootComponent = CollisionComp;
	WeaponMesh->SetupAttachment(CollisionComp);
	SphereTriggerComponent->SetupAttachment(CollisionComp);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereTriggerComponent->GetScaledSphereRadius(), 6, FColor::Turquoise, true, -1, 0, 2);
}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//WeaponMesh->AddRelativeRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	//IsPickup();
	if (MyPawn && bIsHolding == true)
	{

		SetActorLocation(MyPawn->GetActorLocation());

	}
}


void AWeapon::IsPickup()
{
	UE_LOG(LogTemp, Warning, TEXT("It works"));
	// Call virtual function from subclass - C++.
	OnPickUp();

	// Call virtual function from Blueprint.
	//ReceiveOnPickUp();

	// Turn off collisions to stop generate Actor Overlap events.
	//SphereTriggerComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Set invisible.
	//MeshComponent->SetVisibility(false, true);
}

void AWeapon::SetOwningPawn(APlayerCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		Instigator = NewOwner;
		MyPawn = NewOwner;
	}
}

void AWeapon::AttachToPlayer()
{
	if (MyPawn)
	{
		DetachFromPlayer();
		UE_LOG(LogTemp, Warning, TEXT("AWeapon::AttachToPlayer()"));
		USkeletalMeshComponent* Character = MyPawn->GetMesh();
		WeaponMesh->SetHiddenInGame(false);
		WeaponMesh->AttachTo(Character, "Weapon_socket");
	}
}

void AWeapon::DetachFromPlayer()
{
	WeaponMesh->DetachFromParent();
	if (MyPawn)
	{

		SetActorLocation(MyPawn->GetActorLocation());
		
	}
	//WeaponMesh->SetHiddenInGame(true);
}

void AWeapon::OnEquip()
{
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttachToPlayer();
	UE_LOG(LogTemp, Warning, TEXT("AWeapon::OnEquip()"));
	bIsHolding = true;
}

void AWeapon::OnUnEquip()
{
	DetachFromPlayer();
	bIsHolding = false;
}


