// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTTaskNode.h"

#include "BTT_RotateToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API UBTT_RotateToPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_RotateToPlayer();

protected:
	UPROPERTY(EditAnywhere, Category = Task)
	FIntervalCountdown TickInterval;
	
public:
	/** starts executing pawn action */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	/** called when action is removed from stack (FinishedAborting) by some external event
	*  default behavior: finish task as failed */
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	                            EBTNodeResult::Type TaskResult) override;

//	virtual uint16 GetInstanceMemorySize() const override;
};
