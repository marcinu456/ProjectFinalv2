// By Cookie Core


#include "MeleeWeapon_Gun.h"
#include "Character/MainCharacter.h"
#include "Weapon/Projectile.h"
#include "Components/SkeletalMeshComponent.h"

AMeleeWeapon_Gun::AMeleeWeapon_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void AMeleeWeapon_Gun::OnPickUp()
{
	WeaponHolder->MontageSectionIndex = 4;
	UE_LOG(LogTemp, Warning, TEXT("It works here too"));
	if (WeaponHolder && bIsHolding == true)
	{
		OnFire();
	}
}


void AMeleeWeapon_Gun::OnFire()
{

	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Mesh->GetSocketLocation(FName("Muzzle")), Mesh->GetSocketRotation(FName("Muzzle")));
	}
}
