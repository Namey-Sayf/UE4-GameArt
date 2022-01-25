// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_StalkerFire.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API UBTT_StalkerFire : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = Action)
	bool IsFire;

public:
	UBTT_StalkerFire();

	/** starts executing pawn action */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
