// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_KeepInConePlayer.h"

#include "GameArt/NPC/AIControllerBase.h"

UBTD_KeepInConePlayer::UBTD_KeepInConePlayer()
{
	NodeName = "Keep In Cone To Player";
	FlowAbortMode = EBTFlowAbortMode::Self;

	TickInterval.Interval = (.5f);
	ConeHalfAngle = 15.f;

	bNotifyTick = true;
	bNotifyActivation = false;
	bNotifyDeactivation = true;
}

void UBTD_KeepInConePlayer::InitializeFromAsset(UBehaviorTree& Asset)
{
	ConeHalfAngleDot = FMath::Cos(FMath::DegreesToRadians(ConeHalfAngle));
}

void UBTD_KeepInConePlayer::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	TickInterval.Set(0);
}

void UBTD_KeepInConePlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!TickInterval.Tick(DeltaSeconds))
	{
		return;
	}

	TickInterval.Reset();

	const AAIControllerBase* Controller = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());

	const FVector Direction = Controller->GetSafeDirectionToPlayer();
	const float Angle = Controller->GetDirection().CosineAngle2D(Direction);
	if (Angle < ConeHalfAngleDot || (IsInversed() && Angle > ConeHalfAngleDot))
	{
		OwnerComp.RequestExecution(this);
	}
}

FName UBTD_KeepInConePlayer::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Decorator.KeepInCone.Icon");
}
