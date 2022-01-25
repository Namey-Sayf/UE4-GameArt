// Fill out your copyright notice in the Description page of Project Settings.

#include "Drone.h"

#include "DroneAIController.h"
#include "GravityMovement.h"

// Sets default values
ADrone::ADrone()
{
	AIControllerClass = ADroneAIController::StaticClass();

	Movement = CreateDefaultSubobject<UGravityMovement>(TEXT("Move Gravity"));
	if (Movement)
	{
		Movement->SetUpdatedComponent(CapsuleComponent);
	}
	//AutoPossessAI = EAutoPossessAI::Spawned;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Damage.SetDamage(5);
}

void ADrone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CapsuleComponent)
	{
		CapsuleComponent->OnComponentHit.AddDynamic(this, &ADrone::OnHit);
	}
}

void ADrone::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	const auto AIController = Cast<AAIControllerBase>(NewController);

	if (AIController)
		Movement->AddTargetMove(AIController->GetPlayer());
}

void ADrone::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                   FVector NormalImpulse, const FHitResult& Hit)
{
	const auto charapter = Cast<APlayerCharacter>(OtherActor);

	if (charapter)
	{
		charapter->SetDamage(Damage, FVector::ZeroVector);

		OnDeath(FRotator::ZeroRotator, ExplosionEffect);
	}
}
