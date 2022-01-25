// Fill out your copyright notice in the Description page of Project Settings.


#include "Zealot.h"

#include "ZealotAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameArt/GameArtGameModeBase.h"
#include "GameArt/NPC/AIControllerBase.h"
#include "GameArt/Weapon/Projectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AZealot::AZealot()
{
	AIControllerClass = AZealotAIController::StaticClass();

	Movement = CreateDefaultSubobject<UGravityMovement>(TEXT("Move Gravity"));
	if (Movement)
	{
		Movement->SetUpdatedComponent(CapsuleComponent);
	}

	PWeapons = CreateDefaultSubobject<USceneComponent>(FName("WPoints"));
	PWeapons->SetupAttachment(RootComponent);

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FireRate = (.5f);
	WeaponParam.SetDamage(5);
	WeaponParam.SetSpeed(400.f);
	WeaponParam.SetLengthLife(600);
}

// Called when the game starts or when spawned
void AZealot::BeginPlay()
{
	Super::BeginPlay();

	AGameArtGameModeBase* gameMode = Cast<AGameArtGameModeBase>(GetWorld()->GetAuthGameMode());

	if (!BulletPool)
	{
		BulletPool = gameMode->GetNPCBulletPool();
	}
}

void AZealot::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	const auto AIController = Cast<AAIControllerBase>(NewController);

	if (AIController)
		Movement->AddTargetMove(AIController->GetPlayer());
}

void AZealot::SetFire(bool isFire)
{
	UpdFire = isFire ? &AZealot::UpdateFire : nullptr;
}

void AZealot::UpdateFire(float deltaTime)
{
	TimeFire -= deltaTime;

	if (TimeFire > 0)
		return;

	TimeFire = FireRate;

	const int32 COUNT = 4;
	const auto bullets = BulletPool->GetBullets(COUNT);

	if (bullets)
	{
		const FVector location = GetActorLocation();
		const FRotator rotation = PWeapons->GetComponentRotation(); // GetActorRotation();

		//CountBullet = (CountBullet + 1) % COUNT;
		const int32 addAlpha = (360 / COUNT);
		for (int i = 0, alpha = 0; i < COUNT; i++, alpha += addAlpha)
		{
			const FRotator yawRotation(0, rotation.Yaw + alpha, 0);
			const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
			const FVector newLocation = location + (direction * FVector(80.f, 0.f, 0.f));

			AProjectile* bullet = bullets[i];
		
			bullet->SetActorLocation(newLocation, false, nullptr, ETeleportType::None);
			bullet->SetDirection((direction), WeaponParam.GetSpeed());
			bullet->SetWeapon(WeaponParam);

			bullet->SetActive(true);
		}
	}
}

// Called every frame
void AZealot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UpdFire)
	{
		(this->*UpdFire)(DeltaTime);
	}
}
