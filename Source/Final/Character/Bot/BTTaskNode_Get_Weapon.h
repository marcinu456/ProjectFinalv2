// By Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Get_Weapon.generated.h"

class AMainCharacter;
/**
 * 
 */
UCLASS()
class FINAL_API UBTTaskNode_Get_Weapon : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
