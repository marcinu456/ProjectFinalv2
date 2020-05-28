// By Cookie Core


#include "BTTaskNode_Get_Weapon.h"
#include "BotCharacter.h"
#include "Character/MainCharacter.h"
#include "Weapon/Weapon.h"
#include "Weapon/MeleeWeapon/MeleeWeapon.h"

EBTNodeResult::Type UBTTaskNode_Get_Weapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AController* MyController = Cast<AController>(OwnerComp.GetOwner());
	ABotCharacter* MyCharacter = MyController ? Cast<ABotCharacter>(MyController->GetCharacter()) : nullptr;


	//TODO write pickup weapon by bot
	if (MyCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT(" UBTTaskNode_Get_Weapon"));
		//MyCharacter->PickUpWeapon();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}