// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MeleeWeapon.generated.h"

class AMainCharacter;

UCLASS()
class FINAL_API AMeleeWeapon : public AActor
{
    GENERATED_BODY()

public:
    AMeleeWeapon(const FObjectInitializer& ObjectInitializer);

    // The amount of damage attacks by this weapon do 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =
        MeleeWeapon)
        float AttackDamage;

    // A list of things the melee weapon already hit this swing 
    // Ensures each thing sword passes thru only gets hit once 
    TArray<AActor*> ThingsHit;

    // prevents damage from occurring in frames where 
    // the sword is not swinging 
    bool Swinging;

    // "Stop hitting yourself" - used to check if the  
    // actor holding the weapon is hitting himself 
    AMainCharacter* WeaponHolder;

    // bounding box that determines when melee weapon hit 
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
        UBoxComponent* ProxBox;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
        UStaticMeshComponent* Mesh;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
		class USphereComponent* SphereTriggerComponent;

    UFUNCTION(BlueprintNativeEvent, Category = Collision)
        void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // You shouldn't need this unless you get a compiler error that it can't find this function.
    virtual int Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void Swing();
    void Rest();


    /* Handles input for start attack.*/
    UFUNCTION()
        void AttackStart();


    /* Handles input for end attack.*/
    UFUNCTION()
        void AttackEnd();

    /* Set TimerDeley to activate AttackEnd Function, for each weapon use setup in blueprint*/
    UPROPERTY(EditDefaultsOnly, Category = Setup)
        float TimerDelay = 0.5f;

    void IsPickup();

	
    // Set the Character Owner who pickup the weapon
    void SetCharacterOwner(AMainCharacter* NewOwner);

    /* Attach weapon to Socket in CharacterOwner Mesh */
    void AttachToCharacter();
    /* Attach weapon from Socket in CharacterOwner Mesh */
    void DetachFromCharacter();

    /* Called when Character try Equip Weapon*/
    void OnEquip();

    /* Called when Character try UnEquip Weapon*/
    void OnUnEquip();

    /* Inform if weapon is holding by Character*/
    bool bIsHolding = false;

    virtual void OnPickUp() PURE_VIRTUAL(AMeleeWeapon::OnPickUp, );
};
