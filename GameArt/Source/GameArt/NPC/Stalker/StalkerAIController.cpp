// Fill out your copyright notice in the Description page of Project Settings.


#include "StalkerAIController.h"

// Sets default values
AStalkerAIController::AStalkerAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsLookingTarget = false;
	IsOrientation = true;
}

void AStalkerAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AStalkerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Npc = Cast<AStalker>(InPawn);
	Movement = Cast<UStalkerMovement>(Npc->GetMovementComponent());
}

// Called every frame
void AStalkerAIController::Tick(float DeltaTime)
{
	if (IsLookingTarget || Movement->GetState() == Stalker_Walk)
	{
		const auto rotation = GetDeltaRotationToPlayer(DeltaTime, 50);

		SetControlRotation(rotation);
	}

	Super::Tick(DeltaTime);
}

void AStalkerAIController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	if (!IsOrientation)
		return;

	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		FRotator NewControlRotation = GetControlRotation();
		//UE_LOG(LogTemp, Error, TEXT(" -> FRotator :  - %s"), *NewControlRotation.ToString());
		// Look toward focus

		SetControlRotation(NewControlRotation);

		if (bUpdatePawn)
		{
			const FRotator CurrentPawnRotation = MyPawn->GetActorRotation();
			if (CurrentPawnRotation.Equals(NewControlRotation, 1e-3f) == false)
			{
				MyPawn->FaceRotation(NewControlRotation, DeltaTime);
			}
		}
	}
}

void AStalkerAIController::MoveToPlayer()
{
	const auto Direction = GetPawn()->GetActorForwardVector();

	Movement->AddDirectionMove(Direction);
}

void AStalkerAIController::Stay() const
{
	Movement->SwitchState(Stalker_Stay);
}

void AStalkerAIController::Move() const
{
	Movement->SwitchState(Stalker_Walk);
}

void AStalkerAIController::LookTarget(bool lookTarget)
{
	IsLookingTarget = lookTarget;
}

void AStalkerAIController::SetFire(bool bIsFire)
{
	Npc->SetFire(bIsFire);
}

void AStalkerAIController::SetOrientation(bool isFire)
{
	IsOrientation = isFire;
}
