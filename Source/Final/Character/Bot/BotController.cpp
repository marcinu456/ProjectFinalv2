// Cookie Core


#include "BotController.h"
#include "BotCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"

ABotController::ABotController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Blackboard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComponent"));

	BrainComponent = BehaviorComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));

	// Its important for multiplayer game.
	// With this also bots has player state (and can get points to display in rankings menu).
	bWantsPlayerState = true;
}

void ABotController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABotCharacter* Bot = Cast<ABotCharacter>(InPawn);

	// start behavior
	if (Bot && Bot->BotBehavior)
	{
		if (Bot->BotBehavior->BlackboardAsset)
		{
			Blackboard->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset);
		}

		PlayerObjectKeyID = Blackboard->GetKeyID("PlayerObject");
		StartLocationKeyID = Blackboard->GetKeyID("StartLocation");

		// Now this is set from BT.
		//Blackboard->SetValue<UBlackboardKeyType_Object>(PlayerObjectKeyID, UGameplayStatics::GetPlayerCharacter(this, 0));
		Blackboard->SetValue<UBlackboardKeyType_Vector>(StartLocationKeyID, Bot->GetActorLocation());

		BehaviorComponent->StartTree(*(Bot->BotBehavior));
	}

	// Simpler version
	/* - This is how to do this in BT. You don't need to create components in {ctor} but it is less optimal.
	   - The above version do exactly the same things but allows us to call SetValue before the first run of BT.

	ABotCharacter* Bot = Cast<ABotCharacter>(InPawn);

	if (Bot && Bot->BotBehavior)
	{
		RunBehaviorTree(Bot->BotBehavior);
	}
	*/
}

void ABotController::OnUnPossess()
{
	BehaviorComponent->StopTree();
	/* or
	BrainComponent->StopLogic(TEXT(""));
	   or
	Cast<UBehaviorTreeComponent>(BrainComponent)->StopTree();
	*/

	Super::OnUnPossess();
}

