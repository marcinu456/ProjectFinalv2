// Cookie Core
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
/**
 *
 */
UCLASS()
class FINAL_API ABotController : public AAIController
{
	GENERATED_BODY()

public:
	ABotController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	/* Cached BT component */
	UBehaviorTreeComponent* BehaviorComponent;

	UBlackboardComponent* BlackboardCmp;

	//Start following the player
	void StartFollowingPlayer();
	void SetFollowRange(bool war);
	void SetAttackRange(bool war);

	
	int32 PlayerObjectKeyID;
	int32 StartLocationKeyID;
};
