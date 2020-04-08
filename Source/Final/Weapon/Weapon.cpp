// By Cookie Core

#include "MainCharacter.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
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
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("CoinMesh");

	// 2. Set default parameters.
	/*	You can set any parameters you can change in Blueprint and even more.
		Quite often you will need to call a function instead of setting the property directly.
	*/
	SphereComponent->InitSphereRadius(100.0f); //< Here you call InitSphereRadius, after the ctor you should call SetSphereRadius
	//SphereComponent->bNotifyRigidBodyCollision = true; //< Not needed. Simulation Generates Hit Events.
	//SphereComponent->SetGenerateOverlapEvents(true); //< Not needed.
	SphereComponent->SetCollisionProfileName(TEXT("Trigger"));

	MeshComponent->SetGenerateOverlapEvents(false);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(SphereMeshAsset.Object);
	}

	// 3. Setup attachments.
	/*	Define RootComponet.
		SetupAttachment - attach child to parent - works only in ctor.
		@remarks If you want change hierarchy call AttachToComponent after the ctor.

	*/
	RootComponent = SphereComponent;
	MeshComponent->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereComponent->GetScaledSphereRadius(), 6, FColor::Turquoise, true, -1, 0, 2);
}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MeshComponent->AddRelativeRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	//IsPickup();
}


void AWeapon::IsPickup()
{
	UE_LOG(LogTemp, Warning, TEXT("It works"));
	// Call virtual function from subclass - C++.
	OnPickUp();

	// Call virtual function from Blueprint.
	//ReceiveOnPickUp();

	// Turn off collisions to stop generate Actor Overlap events.
	//SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Set invisible.
	//MeshComponent->SetVisibility(false, true);
}

