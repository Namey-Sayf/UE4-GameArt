// Fill out your copyright notice in the Description page of Project Settings.


#include "StalkerMovement.h"

#include "StalkerAIController.h"

UStalkerMovement::UStalkerMovement() : CurrentState(Stalker_Stay)
{
	WalkSpeed = 400.f;
}

void UStalkerMovement::BeginPlay()
{
	Super::BeginPlay();

	controller = Cast<AStalkerAIController>(GetPawnOwner()->GetController());
}

void UStalkerMovement::SwitchState(const StateMove state)
{
	CurrentState = state;
	Velocity = FVector::ZeroVector;

	switch (state)
	{
	case Stalker_Stay:
		Speed = WalkSpeed;
		TimeMove = 0.f;
		break;

	case Stalker_Walk:
		Speed = WalkSpeed;
		TimeMove = 0.f;
		break;

	default:
		Speed = 0.f;
		TimeMove = 0.f;
		break;
	}
}

void UStalkerMovement::AddDirectionMove(const FVector direction)
{
	if (CurrentState != Stalker_Walk)
		SwitchState(Stalker_Walk);

	//UE_LOG(LogTemp, Error, TEXT(" -> Delta : %d"), Speed);
	Velocity = direction * Speed;
}

void UStalkerMovement::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent)
	{
		return;
	}

	const AController* Controller = PawnOwner->GetController();
	if (Controller && Controller->IsLocalController())
	{
		// if it's not player controller, but we do have a controller, then it's AI
		// (that's not following a path) and we need to limit the speed
		if (IsExceedingMaxSpeed(Speed) == true)
		{
			Velocity = Velocity.GetUnsafeNormal() * Speed;
		}

		FVector Delta = Velocity * DeltaTime;
		if (!Delta.IsNearlyZero(1e-6f))
		{
			const FVector OldLocation = UpdatedComponent->GetComponentLocation();
			const FQuat Rotation = UpdatedComponent->GetComponentQuat();

			FHitResult Hit(1.f);
			SafeMoveUpdatedComponent(Delta, Rotation, true, Hit);

			if (Hit.IsValidBlockingHit())
			{
				HandleImpact(Hit, DeltaTime, Delta);
				// Try to slide the remaining distance along the surface.
				SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit, true);
			}

			// Update velocity
			// We don't want position changes to vastly reverse our direction (which can happen due to penetration fixups etc)
			//if (!bPositionCorrected)
			{
				const FVector NewLocation = UpdatedComponent->GetComponentLocation();
				Velocity = ((NewLocation - OldLocation) / DeltaTime);
			}
		}

		// Finalize
		UpdateComponentVelocity();
	}
}
