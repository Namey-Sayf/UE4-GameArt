// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_SetFire.h"

#include "GameArt/NPC/AIControllerBase.h"


UBTT_SetFire::UBTT_SetFire()
{
	NodeName = "Set Fire";
}

EBTNodeResult::Type UBTT_SetFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto controller = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());

	if (controller)
	{
		controller->SetFire(IsFire);

		return EBTNodeResult::Type::Succeeded;
	}

	return EBTNodeResult::Type::Failed;
}
