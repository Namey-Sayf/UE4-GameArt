// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_DistanceToPlayer.h"

#include "GameArt/NPC/AIControllerBase.h"

UBTD_DistanceToPlayer::UBTD_DistanceToPlayer()
{
	NodeName = "Distance To Player";
	FlowAbortMode = EBTFlowAbortMode::Self;
	
	Distance = 500.f;
}

bool UBTD_DistanceToPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto controller = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());

	if (controller)
	{
		const float distance = controller->GetDistanceToPlayer();

		const int32 dist = Distance * Distance;
		return IsUpper
			       ? (dist < distance)
			       : (dist > distance);
	}
	
	return false;
}
