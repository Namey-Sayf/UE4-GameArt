// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Zealot.h"
#include "GameArt/NPC/AIControllerBase.h"

#include "ZealotAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API AZealotAIController : public AAIControllerBase
{
	GENERATED_BODY()

	AZealot* Npc;

public:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetFire(bool isFire) override;
};
