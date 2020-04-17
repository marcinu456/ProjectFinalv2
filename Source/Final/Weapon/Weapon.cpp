// By Cookie Core


#include "Weapon.h"
#include "Character/MainCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"


// Sets default values
AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>("CollisionComp");
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	BladeMesh = CreateDefaultSubobject<UCapsuleComponent>("BladeMesh"); //Check CollisionProfile
	
	SphereTriggerComponent = CreateDefaultSubobject<USphereComponent>("SphereTriggerComponent");
	SphereTriggerComponent->InitSphereRadius(100.0f);
	SphereTriggerComponent->SetCollisionProfileName(TEXT("Trigger"));
	
	RootComponent = CollisionComp;
	WeaponMesh->SetupAttachment(CollisionComp);
	BladeMesh->SetupAttachment(WeaponMesh);
	SphereTriggerComponent->SetupAttachment(CollisionComp);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	//DrawDebugSphere(GetWorld(), GetActorLocation(), SphereTriggerComponent->GetScaledSphereRadius(), 6, FColor::Turquoise, true, -1, 0, 2);
}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//WeaponMesh->AddRelativeRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	if (CharacterOwner && bIsHolding == true)
	{

		SetActorLocation(CharacterOwner->GetActorLocation());

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

/* Set the Character Owner who pickup the weapon*/
void AWeapon::SetCharacterOwner(AMainCharacter* NewOwner)
{
	if (CharacterOwner != NewOwner)
	{
		CharacterOwner = NewOwner;
	}
}

/* Attach weapon to Socket in CharacterOwner Mesh */
void AWeapon::AttachToCharacter()
{
	if (CharacterOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
		UE_LOG(LogTemp, Warning, TEXT("Character name: %s"), *(CharacterOwner->GetName()));
		DetachFromCharacter();
		USkeletalMeshComponent* Character = CharacterOwner->GetMesh();
		WeaponMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		WeaponMesh->SetHiddenInGame(false);
		WeaponMesh->AttachTo(Character, "Weapon_socket");

	}
}

/* Attach weapon from Socket in CharacterOwner Mesh */
void AWeapon::DetachFromCharacter()
{
	WeaponMesh->DetachFromParent();
	if (CharacterOwner)
	{

		SetActorLocation(CharacterOwner->GetActorLocation());
		WeaponMesh->SetRelativeLocation(CharacterOwner->GetActorLocation());
	}
}

/* Called when Character try Equip Weapon*/
void AWeapon::OnEquip()
{
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttachToCharacter();
	bIsHolding = true;
}

/* Called when Character try UnEquip Weapon*/
void AWeapon::OnUnEquip()
{
	DetachFromCharacter();
	bIsHolding = false;
}


