// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameArt/NPC/AIControllerBase.h"
#include "DroneAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API ADroneAIController : public AAIControllerBase
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;
};
