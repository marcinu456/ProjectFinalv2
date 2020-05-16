// By Cookie Core


#include "Gun.h"
#include "Character/MainCharacter.h"
#include "Weapon/Projectile.h"
#include "Components/SkeletalMeshComponent.h"

AGun::AGun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void AGun::OnPickUp()
{
	CharacterOwner->MontageSectionIndex = 4;
	UE_LOG(LogTemp, Warning, TEXT("It works here too"));
	if (CharacterOwner && bIsHolding == true)
	{
		OnFire();
	}
}


void AGun::OnFire()
{

	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, WeaponMesh->GetSocketLocation(FName("Muzzle")), WeaponMesh->GetSocketRotation(FName("Muzzle")));
	}
}