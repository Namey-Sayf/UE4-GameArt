// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameArt/Player/PlayerCharacter.h"

#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();

	UPROPERTY(EditAnywhere, Category = AII, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* TBehaviorTree;

	virtual void LookTarget(bool lookTarget);
	virtual void SetFire(bool isFire);

protected:
	APlayerCharacter* Player;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;


public:
	float GetDistanceToPlayer() const;
	FVector GetDirectionToPlayer() const;
	FVector GetSafeDirectionToPlayer() const;
	FVector GetDirection() const;
	FVector GetLocation() const;
	FVector GetPlayerLocation() const;
	FRotator GetRotationToPlayer() const;
	FRotator GetDeltaRotationToPlayer(float delta, float speed = 10) const;
	APlayerCharacter* GetPlayer() const { return Player; };

private:
	const FVector GetRawDirectionToPlayer() const;
};
