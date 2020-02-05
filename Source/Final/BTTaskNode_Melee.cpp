// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Melee.h"
#include "BotCharacter.h"

EBTNodeResult::Type UBTTaskNode_Melee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AController* MyController = Cast<AController>(OwnerComp.GetOwner());
	ABotCharacter* MyCharacter = MyController ? Cast<ABotCharacter>(MyController->GetCharacter()) : nullptr;

	if (MyCharacter)
	{
		int MontageSectionIndex = rand() % 2 + 1;

		// fstring animation section
		FString MontageSection = "Start_" + FString::FromInt(MontageSectionIndex);

		MyCharacter->PlayAnimMontage(MyCharacter->MeleeFistAttackMontage, 1.f, FName(*MontageSection));
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

