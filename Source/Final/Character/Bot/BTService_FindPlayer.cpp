// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTService_FindPlayer::UBTService_FindPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Find player in radius";

	// Accept only actor.
	PlayerKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_FindPlayer, PlayerKey), AActor::StaticClass());

	// Enable tick.
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;

	// Set default value.
	PlayerKey.SelectedKeyName = TEXT("Enemy");
	SearchRadius = 1000.0f;
	bIsLOS = false;
}

void UBTService_FindPlayer::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		PlayerKey.ResolveSelectedKey(*BBAsset);
	}
}

FString UBTService_FindPlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s\nFind %s in radius %.2f %s"),
		*Super::GetStaticDescription(),
		*PlayerKey.SelectedKeyName.ToString(),
		SearchRadius,
		bIsLOS ? TEXT(" in LOS") : TEXT(""));
}

void UBTService_FindPlayer::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	FindPlayer(OwnerComp);
}

void UBTService_FindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FindPlayer(OwnerComp);
}

void UBTService_FindPlayer::FindPlayer(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == NULL)
	{
		return;
	}

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = OwnerController->GetPawn();

	AActor* CurrentPlayer = Cast<AActor>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(PlayerKey.GetSelectedKeyID()));
	AActor* BestPlayer = nullptr;
	float BestDistance = FLT_MAX;

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		// Get player actor.
		APlayerController* PlayerController = It->Get();
		AActor* TestPlayer = PlayerController->GetPawn();
		if (!TestPlayer)
			continue;

		// Check distance.
		float TestDistance = OwnerPawn->GetDistanceTo(TestPlayer);
		if (TestDistance > SearchRadius)
			continue;

		// Check LOS (if needed).
		if (bIsLOS && !OwnerController->LineOfSightTo(TestPlayer))
			continue;

		// If previous player then use it.
		if (TestPlayer == CurrentPlayer)
		{
			BestPlayer = TestPlayer;
			BestDistance = TestDistance;
			break;
		}

		// Check if closer then previous best.
		if (BestPlayer && BestDistance < TestDistance)
			continue;

		// Remember the new best.
		BestPlayer = TestPlayer;
		BestDistance = TestDistance;
	}

	BlackboardComp->SetValue<UBlackboardKeyType_Object>(PlayerKey.GetSelectedKeyID(), BestPlayer);
}
