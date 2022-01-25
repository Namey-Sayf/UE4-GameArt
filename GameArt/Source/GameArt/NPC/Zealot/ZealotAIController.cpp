// Fill out your copyright notice in the Description page of Project Settings.

#include "ZealotAIController.h"

void AZealotAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	Npc = Cast<AZealot>(InPawn);
}

void AZealotAIController::SetFire(bool isFire)
{
	Npc->SetFire(isFire);
}
