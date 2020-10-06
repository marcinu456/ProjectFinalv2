// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindPlayer.generated.h"


struct FBTFindPlayerMemory
{
	// Add instance variable here. Use POD without UPROPERTY.
};
/**
 * 
 */
UCLASS()
class FINAL_API UBTService_FindPlayer : public UBTService
{
	GENERATED_BODY()
	
	typedef FBTFindPlayerMemory TNodeInstanceMemory;

public:
	UBTService_FindPlayer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Minimal distance to search for player. */
	UPROPERTY(EditAnywhere, Category = Params)
		float SearchRadius;

	/** Is line of sight to player required? */
	UPROPERTY(EditAnywhere, Category = Params)
		bool bIsLOS;

	/** Out player actor key. */
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector PlayerKey;

protected:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual uint16 GetInstanceMemorySize() const override { return sizeof(TNodeInstanceMemory); }
	virtual FString GetStaticDescription() const override;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void FindPlayer(UBehaviorTreeComponent& OwnerComp);
};
