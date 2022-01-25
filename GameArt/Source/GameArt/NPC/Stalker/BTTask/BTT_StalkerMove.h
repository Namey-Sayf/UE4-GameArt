// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameArt/NPC/Stalker/StalkerAIController.h"
#include "BTT_StalkerMove.generated.h"


struct FMemmoryStalkerMove 
{
	AStalkerAIController* controller;
};
/**
 * 
 */
UCLASS()
class GAMEART_API UBTT_StalkerMove : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_StalkerMove();

protected:
	UPROPERTY(EditAnywhere, Category = Task)
	FIntervalCountdown TickInterval;

public:
	/** starts executing pawn action */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	/** action observer, updates state of task */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	/** called when action is removed from stack (FinishedAborting) by some external event
	*  default behavior: finish task as failed */
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	                            EBTNodeResult::Type TaskResult) override;

	virtual uint16 GetInstanceMemorySize() const override;
};
