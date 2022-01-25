// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Stalker.h"
#include "GameArt/NPC/AIControllerBase.h"
#include "StalkerAIController.generated.h"

UCLASS()
class GAMEART_API AStalkerAIController : public AAIControllerBase
{
	GENERATED_BODY()

	UStalkerMovement* Movement;

	AStalker* Npc;

	bool IsLookingTarget;
	bool IsOrientation;
	
public:
	// Sets default values for this actor's properties
	AStalkerAIController();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void OnPossess(APawn* InPawn) override;

	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE bool IsPlayerTarget() const { return GetPlayer() != nullptr; };
	void MoveToPlayer();
	void Stay() const;
	void Move() const;
	
	void SetOrientation(bool isFire);

	//FORCEINLINE StateMove GetMovementStatus() const;
	virtual void LookTarget(bool lookTarget) override;

	virtual void SetFire(bool isFire) override;
	
private:

};
