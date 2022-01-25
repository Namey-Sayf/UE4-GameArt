// Fill out your copyright notice in the Description page of Project Settings.


#include "Stalker.h"

#include "StalkerAIController.h"
#include "GameArt/GameArtGameModeBase.h"
#include "GameArt/Weapon/Projectile.h"

AStalker::AStalker()
{
	Movement = CreateDefaultSubobject<UStalkerMovement>(TEXT("Move Stalker"));
	if (Movement)
	{
		Movement->UpdatedComponent = CapsuleComponent;
	}

	AIControllerClass = AStalkerAIController::StaticClass();

	PWeapons = CreateDefaultSubobject<USceneComponent>(FName("WPoints"));
	PWeapons->SetupAttachment(RootComponent);
	PWeapons->SetRelativeLocation(FVector(100, 0, 0));
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FireRate = (.6f);
	WeaponParam.SetDamage(5);
	WeaponParam.SetSpeed(400.f);
	WeaponParam.SetLengthLife(800);
}

void AStalker::BeginPlay()
{
	Super::BeginPlay();

	AGameArtGameModeBase* gameMode = Cast<AGameArtGameModeBase>(GetWorld()->GetAuthGameMode());

	if (!BulletPool)
	{
		BulletPool = gameMode->GetNPCBulletPool();
	}
}

void AStalker::UpdateFire(float deltaTime)
{
	TimeFire -= deltaTime;

	if (TimeFire > 0)
		return;

	TimeFire = FireRate;

	//const int32 COUNT = 4;
	AProjectile* bullets = BulletPool->GetBullet();

	if (bullets)
	{
		const FVector location = PWeapons->GetComponentLocation(); // GetActorLocation();
		//const FRotator rotation = PWeapons->GetComponentRotation(); // GetActorRotation();

		//for (int i = 0, alpha = 0; i < COUNT; i++, alpha += 90)
		{
			//const FRotator yawRotation(0, rotation.Yaw + alpha, 0);
			const FVector direction = FRotationMatrix(GetActorRotation()).GetUnitAxis(EAxis::X);
			//const FVector newLocation = location + (direction * FVector(40.f, 0.f, 0.f));

			bullets->SetActorLocation(location, false, nullptr, ETeleportType::None);
			bullets->SetDirection(direction, WeaponParam.GetSpeed());
			bullets->SetWeapon(WeaponParam);
			bullets->SetActive(true);
		}
	}
}

void AStalker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UpdFire)
	{
		(this->*UpdFire)(DeltaTime);
	}
}

void AStalker::SetFire(bool isFire)
{
	UpdFire = isFire ? &AStalker::UpdateFire : nullptr;
}
