// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityMovement.h"

UGravityMovement::UGravityMovement() : TargetMove(nullptr)
{
	MaxSpeed = 500.f;
	MinSpeed = 100.f;
}

void UGravityMovement::BeginPlay()
{
	Super::BeginPlay();

	MaxSpeed += FMath::RandRange(0.f, MaxSpeed * .5f);
}

FORCEINLINE void UGravityMovement::AddTargetMove(AActor* target)
{
	TargetMove = target;
}

FORCEINLINE void UGravityMovement::AddGravity(const AActor* origin, const AActor* target)
{
	CalcGravity(origin, target);
}

FORCEINLINE void UGravityMovement::AddGravity(const FVector origin, const FVector target)
{
	CalcGravity(origin, target);
}

FORCEINLINE void UGravityMovement::AddGravity(const FVector direction, float distance)
{
	CalcGravity(direction, distance);
}

void UGravityMovement::SetMove(bool isMove)
{
	SetComponentTickEnabled(isMove);
}

FORCEINLINE void UGravityMovement::CalcTargetGravity()
{
	const FVector orgLocation = GetActorLocation();
	const FVector tarLocation = TargetMove->GetActorLocation();

	CalcGravity(orgLocation, tarLocation);
}

FORCEINLINE void UGravityMovement::CalcGravity(const AActor* origin, const AActor* target)
{
	const FVector orgLocation = origin->GetActorLocation();
	const FVector tarLocation = target->GetActorLocation();

	CalcGravity(orgLocation, tarLocation);
}

FORCEINLINE void UGravityMovement::CalcGravity(const FVector origin, const FVector target)
{
	const float distance = FVector::DistXY(target, origin);
	const FVector direction = (target - origin).GetUnsafeNormal();

	CalcGravity(direction, distance);
}

FORCEINLINE void UGravityMovement::CalcGravity(const FVector direction, float distance)
{
	float newSpeed = distance > 0 ? MaxSpeed / distance : MaxSpeed;

	if (distance > 800)
	{
		Velocity = FVector::ZeroVector;
	}

	if (newSpeed < MinSpeed)
		newSpeed = MinSpeed;
	
	Velocity = Velocity + (direction * newSpeed);

	if (IsExceedingMaxSpeed(MaxSpeed))
	{
		Velocity = Velocity.GetUnsafeNormal() * MaxSpeed;
	}
}

void UGravityMovement::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
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

	if (TargetMove)
	{
		CalcTargetGravity();
	}

	const AController* Controller = PawnOwner->GetController();
	if (Controller && Controller->IsLocalController())
	{
		// if it's not player controller, but we do have a controller, then it's AI
		// (that's not following a path) and we need to limit the speed
		// if (IsExceedingMaxSpeed(MaxSpeed) == true)
		// {
		// 	Velocity = Velocity.GetUnsafeNormal() * MaxSpeed;
		// }

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
