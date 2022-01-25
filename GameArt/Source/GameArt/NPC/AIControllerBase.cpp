// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"

//#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
AAIControllerBase::AAIControllerBase()
{
	//UKismetMathLibrary::()
	//UGameplayStatics::()
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	const auto playerController = GetWorld()->GetFirstPlayerController();
	
	if (playerController)
	{
		Player = Cast<APlayerCharacter>(playerController->GetPawn());
	}
}

FORCEINLINE float AAIControllerBase::GetDistanceToPlayer() const
{
	const FVector playerLocation = Player->GetActorLocation();
	const FVector currLocation = GetPawn()->GetActorLocation();

	return FVector::DistSquaredXY(playerLocation, currLocation);
}

FORCEINLINE FVector AAIControllerBase::GetDirectionToPlayer() const
{
	return GetRawDirectionToPlayer().GetUnsafeNormal2D();
}

FORCEINLINE FVector AAIControllerBase::GetSafeDirectionToPlayer() const
{
	return GetRawDirectionToPlayer().GetSafeNormal2D();
}

FORCEINLINE const FVector AAIControllerBase::GetRawDirectionToPlayer() const
{
	const FVector playerLocation = Player->GetActorLocation();
	const FVector currLocation = GetPawn()->GetActorLocation();
	
	return (playerLocation - currLocation);
}

FORCEINLINE FVector AAIControllerBase::GetDirection() const
{
	return GetPawn()->GetActorForwardVector();
}

FORCEINLINE FVector AAIControllerBase::GetLocation() const
{
	return GetPawn()->GetActorLocation();
}

FORCEINLINE FVector AAIControllerBase::GetPlayerLocation() const
{
	return Player->GetActorLocation();
}

FORCEINLINE FRotator AAIControllerBase::GetRotationToPlayer() const
{
	return Player->GetActorRotation(); // GetDirectionToPlayer().Rotation();
}

FORCEINLINE FRotator AAIControllerBase::GetDeltaRotationToPlayer(float delta, float speed) const
{
	const FVector Result = GetDirectionToPlayer();

	return FMath::RInterpConstantTo(GetControlRotation(), Result.Rotation(), delta, speed);
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!TBehaviorTree)
	{
		return;
	}

	const bool isBTree = RunBehaviorTree(TBehaviorTree);

	if (!isBTree)
	{
		UE_LOG(LogTemp, Error, TEXT(" -> RunBehaviorTree is fail !"));
	}
}

void AAIControllerBase::LookTarget(bool lookTarget)
{
	// EMPTY
}

void AAIControllerBase::SetFire(bool isFire)
{
	// EMPTY
}

