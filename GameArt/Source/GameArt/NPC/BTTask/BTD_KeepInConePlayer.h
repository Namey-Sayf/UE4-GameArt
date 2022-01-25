// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "GameArt/NPC/AIControllerBase.h"
#include "BTD_KeepInConePlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API UBTD_KeepInConePlayer : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTD_KeepInConePlayer();

protected:
	UPROPERTY(EditAnywhere, Category = Task)
	FIntervalCountdown TickInterval;
	
	UPROPERTY(Category = Decorator, EditAnywhere)
	float ConeHalfAngle;

	float ConeHalfAngleDot;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
	/** called when underlying node has finished
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif // WITH_EDITOR
};
