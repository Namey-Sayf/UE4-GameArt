// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"

#include "GravityMovement.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API UGravityMovement : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UGravityMovement();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Movement)
	float MaxSpeed;

	UPROPERTY(EditAnywhere, Category = Movement)
	float MinSpeed;
	
	AActor* TargetMove;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetMove(bool isMove);
	void AddTargetMove(AActor* target);

	void AddGravity(const AActor* origin, const AActor* target);
	void AddGravity(const FVector origin, const FVector target);
	void AddGravity(const FVector direction, float distance);

private:
	void CalcTargetGravity();

	void CalcGravity(const AActor* origin, const AActor* target);
	void CalcGravity(const FVector origin, const FVector target);
	void CalcGravity(const FVector direction, float distance);
};
