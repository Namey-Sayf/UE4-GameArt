// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_DistanceToPlayer.generated.h"

class AAIControllerBase;

/**
 * 
 */
UCLASS()
class GAMEART_API UBTD_DistanceToPlayer : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_DistanceToPlayer();

protected:
	UPROPERTY(Category = Value, EditAnywhere)
	int32 Distance;
	
	UPROPERTY(Category = Value, EditAnywhere)
	bool IsUpper;
	
	/** calculates raw, core value of decorator's condition. Should not include calling IsInversed */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
