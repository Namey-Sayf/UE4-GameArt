// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameArtyGameState.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API AGameArtyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	int32 CountNpcLife;

	int32 GetCountNpcLife() { return CountNpcLife; }

	void SetCountNpc(int32 count);
};
