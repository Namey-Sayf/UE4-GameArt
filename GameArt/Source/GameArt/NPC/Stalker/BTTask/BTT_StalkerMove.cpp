// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_StalkerMove.h"

UBTT_StalkerMove::UBTT_StalkerMove()
{
	TickInterval.Interval = (.2f);
	NodeName = "Stalker Move To Player";
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTT_StalkerMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!NodeMemory)
		return EBTNodeResult::Type::Aborted;

	FMemmoryStalkerMove* memmory = reinterpret_cast<FMemmoryStalkerMove*>(NodeMemory);

	memmory->controller = Cast<AStalkerAIController>(OwnerComp.GetAIOwner());

	if (memmory->controller)
		return EBTNodeResult::Type::InProgress;
	else
		return EBTNodeResult::Type::Aborted;
}

void UBTT_StalkerMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!TickInterval.Tick(DeltaSeconds))
	{
		return;
	}

	TickInterval.Reset();

	if (NodeMemory == nullptr)
	{
		FinishLatentAbort(OwnerComp);
		return;
	}

	FMemmoryStalkerMove* memmory = reinterpret_cast<FMemmoryStalkerMove*>(NodeMemory);

	if (memmory->controller)
		memmory->controller->MoveToPlayer();
	else
	{
		FinishLatentAbort(OwnerComp);
	}
}

void UBTT_StalkerMove::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                      EBTNodeResult::Type TaskResult)
{
	FMemmoryStalkerMove* memmory = reinterpret_cast<FMemmoryStalkerMove*>(NodeMemory);

	if (memmory->controller)
		memmory->controller->Stay();

	TickInterval.Set(0);
}

uint16 UBTT_StalkerMove::GetInstanceMemorySize() const
{
	return sizeof(FMemmoryStalkerMove);
}
