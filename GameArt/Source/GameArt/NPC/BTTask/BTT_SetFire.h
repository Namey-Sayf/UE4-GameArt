// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTTaskNode.h"

#include "BTT_SetFire.generated.h"

UCLASS()
class GAMEART_API UBTT_SetFire : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_SetFire();

private:
	UPROPERTY(EditAnywhere, Category = Task)
	bool IsFire;

	/** starts executing pawn action */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
