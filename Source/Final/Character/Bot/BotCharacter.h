// Cookie Core

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(EditAnywhere, Category = Behavior)
		class	UBehaviorTree* BotBehavior;

	/* Create Trigger Capsule to get weapon*/
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		class UCapsuleComponent* TriggerCapsule;

	void PickUpWeapon();

};