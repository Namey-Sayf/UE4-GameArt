// Fill out your copyright notice in the Description page of Project Settings.

#include "DroneAIController.h"

void ADroneAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!GetPlayer())
	{
		SetActorTickEnabled(false);
		return;
	}
}
