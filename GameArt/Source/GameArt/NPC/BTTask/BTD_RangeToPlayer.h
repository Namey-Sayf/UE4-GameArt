// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_RangeToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API UBTD_RangeToPlayer : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTD_RangeToPlayer();

protected:
	UPROPERTY(EditAnywhere, Category = Task)
	FIntervalCountdown TickInterval;

	UPROPERTY(Category = Value, EditAnywhere)
	int32 Distance;

	UPROPERTY(Category = Value, EditAnywhere)
	bool IsUpper;
	
	/** called when underlying node has finished
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
