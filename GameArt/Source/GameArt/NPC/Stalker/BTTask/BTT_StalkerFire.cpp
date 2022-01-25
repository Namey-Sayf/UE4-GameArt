// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_StalkerFire.h"

#include "GameArt/NPC/Stalker/StalkerAIController.h"

UBTT_StalkerFire::UBTT_StalkerFire()
{
	//bNotifyTaskFinished = false;
	//bNotifyTick = false;
}

EBTNodeResult::Type UBTT_StalkerFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto controller = Cast<AStalkerAIController>(OwnerComp.GetAIOwner());

	if (controller)
	{
		controller->SetFire(IsFire);

		return EBTNodeResult::Type::Succeeded;
	}

	return EBTNodeResult::Type::Failed;
}
