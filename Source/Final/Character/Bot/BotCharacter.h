// Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Final/Character/MainCharacter.h"
#include "GameFramework/Character.h"
#include "BotCharacter.generated.h"

class AWeapon;

/**
 *
 */
UCLASS()
class FINAL_API ABotCharacter : public AMainCharacter
{
	GENERATED_BODY()
public:
	ABotCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = Behavior)
		class	UBehaviorTree* BotBehavior;

	/* Create Trigger Capsule to get weapon*/
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		class UCapsuleComponent* TriggerCapsule;

	void PickUpWeapon();

    // How fast he is 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
        float Speed;

    // The hitpoints the monster has 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
        float HitPoints;

    // Experience gained for defeating 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
        int32 Experience;

    // Blueprint of the type of item dropped by the monster 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
        UClass* BPLoot;

    // The amount of damage attacks do 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
        float BaseAttackDamage;

    // Amount of time the monster needs to rest in seconds 
    // between attacking 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
        float AttackTimeout;

    // Time since monster's last strike, readable in blueprints 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
        float TimeSinceLastStrike;

    // Range for his sight 
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
        USphereComponent* SightSphere;

    // Range for his attack. Visualizes as a sphere in editor, 
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
        USphereComponent* AttackRangeSphere;

    UFUNCTION(BlueprintCallable, Category = Collision)
    inline bool isInSightRange(float d)
    {
        return d < SightSphere->GetScaledSphereRadius();
    }
    UFUNCTION(BlueprintCallable, Category = Collision)
    inline bool isInAttackRange(float d)
    {
        return d < AttackRangeSphere->GetScaledSphereRadius();
    }

    UFUNCTION(BlueprintCallable, Category = Collision)
        void AtackMeleeWeapon();

	
};