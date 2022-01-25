// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_ConeCheckPlayer.h"

#include "GameArt/NPC/AIControllerBase.h"

UBTD_ConeCheckPlayer::UBTD_ConeCheckPlayer()
{
	NodeName = "Cone Check To Player";
	FlowAbortMode = EBTFlowAbortMode::Self;

	TickInterval.Interval = (.5f);
	ConeHalfAngle = 15.f;

	bNotifyTick = true;
	bNotifyActivation = false;
	bNotifyDeactivation = true;
}

void UBTD_ConeCheckPlayer::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	TickInterval.Set(0);
}

void UBTD_ConeCheckPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!TickInterval.Tick(DeltaSeconds))
	{
		return;
	}

	TickInterval.Reset();

	const AAIControllerBase* Controller = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());

	if (Controller)
	{
		const FVector ConeDir = Controller->GetDirection();
		const FVector DirectionToObserve = Controller->GetDirectionToPlayer();

		if (ConeDir.CosineAngle2D(DirectionToObserve) > ConeHalfAngleDot)
		{
			OwnerComp.RequestExecution(this);
		}
	}
}

void UBTD_ConeCheckPlayer::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	ConeHalfAngleDot = FMath::Cos(FMath::DegreesToRadians(ConeHalfAngle));
}

FName UBTD_ConeCheckPlayer::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Decorator.ConeCheck.Icon");
}
