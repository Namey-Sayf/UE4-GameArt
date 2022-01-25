// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_RangeToPlayer.h"

#include "GameArt/NPC/AIControllerBase.h"

UBTD_RangeToPlayer::UBTD_RangeToPlayer()
{
	NodeName = "Range To Player";
	FlowAbortMode = EBTFlowAbortMode::Self;

	TickInterval.Interval = (.5f);
	Distance = 500.f;

	bNotifyTick = true;
	bNotifyActivation = false;
	bNotifyDeactivation = true;
}

void UBTD_RangeToPlayer::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	TickInterval.Set(0);
}

void UBTD_RangeToPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!TickInterval.Tick(DeltaSeconds))
	{
		return;
	}

	TickInterval.Reset();

	const auto controller = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());

	if (controller)
	{
		const float distance = controller->GetDistanceToPlayer();
		const int32 dist = Distance * Distance;
		const bool isDistance = IsUpper
			                        ? (dist < distance)
			                        : (dist > distance);

		if (!isDistance)
		{
			OwnerComp.RequestExecution(this);
		}
	}
}
