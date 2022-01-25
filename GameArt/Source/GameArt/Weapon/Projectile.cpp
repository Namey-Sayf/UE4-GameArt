// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Damagable/Damagable.h"
#include "GameArt/Player/GPlayerController.h"

// Sets default values
AProjectile::AProjectile() : TimeLife(2.f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(10.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	//CollisionComponent->SetNotifyRigidBodyCollision(true);
	//CollisionComponent->bTraceComplexOnMove = true;

	RootComponent = CollisionComponent;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(CollisionComponent);

	MovementComponent->InitialSpeed = 500.0f;

	MovementComponent->MaxSpeed = 5000.0f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bShouldBounce = false;
	MovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CollisionComponent)
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	//CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT(" OnHit() "));
	SetActive(false);
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT(" OnOverlapBegin() "));

	const auto damagable = Cast<IDamagable>(OtherActor);

	if (damagable)
	{
		damagable->SetDamage(Damage, GetVelocity());

		if (DeathEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathEffect, SweepResult.Location);
		}
	}

	SetActive(false);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeLife -= DeltaTime;

	if (TimeLife < 0)
	{
		SetActive(false);
	}
}

void AProjectile::SetActive(bool isActive)
{
	TimeLife = Damage.GetLifeTime();

	SetActorHiddenInGame(!isActive);
	SetActorEnableCollision(isActive);
	SetActorTickEnabled(isActive);
	MovementComponent->SetActive(isActive);
}

void AProjectile::SetDirection(FVector direction, float speed) const
{
	if (MovementComponent)
	{
		MovementComponent->Velocity = (direction * speed);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("-> nullptr - MovementComponent"));
	}
}
