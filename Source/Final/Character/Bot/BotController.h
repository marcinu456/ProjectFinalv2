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

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	/* Cached BT component */
	UPROPERTY(transient)
		UBehaviorTreeComponent* BehaviorComponent;

	int32 PlayerObjectKeyID;
	int32 StartLocationKeyID;
};
