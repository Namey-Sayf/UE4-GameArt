// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_RotateToPlayer.h"

#include "GameArt/NPC/AIControllerBase.h"

UBTT_RotateToPlayer::UBTT_RotateToPlayer()
{
	NodeName = "Rotate To Player";
	
	bNotifyTick = false;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTT_RotateToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto controller = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());

	if (controller)
	{
		controller->LookTarget(true);

		return EBTNodeResult::Type::InProgress;
	}

	return EBTNodeResult::Type::Failed;
}


void UBTT_RotateToPlayer::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                         EBTNodeResult::Type TaskResult)
{
	const auto controller = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());

	if (controller)
	{
		controller->LookTarget(false);
	}
}
