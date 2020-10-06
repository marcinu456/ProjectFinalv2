// By Cookie Core


#include "MeleeWeapon_Gun.h"
#include "Final/Character/MainCharacter.h"
#include "Projectile.h"
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
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMeleeWeapon_Gun::OnFire, 0.2f, true, 0.2f);
		
	}
}


void AMeleeWeapon_Gun::OnFire()
{

	 //try and fire a projectile
	if (ProjectileClass != NULL)
	{
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Mesh->GetSocketLocation(FName("Muzzle")), Mesh->GetSocketRotation(FName("Muzzle")));
	}
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}