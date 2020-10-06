// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FollowPlayer.h"
#include "BotController.h"


EBTNodeResult::Type UBTTaskNode_FollowPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ABotController* Controller = Cast<ABotController>(OwnerComp.GetAIOwner());
    if (Controller == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Controller->StartFollowingPlayer();

    return EBTNodeResult::Succeeded;
}