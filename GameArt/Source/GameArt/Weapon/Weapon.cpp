#include "Weapon.h"

#include "Projectile.h"

//#include "Kismet/KismetSystemLibrary.h"

//Kismet.System.Library
BWeapon::BWeapon() : FireWait(0), Bullet(nullptr)
{
	BulletParams.SetSpeed(2500.f);
	BulletParams.SetLengthLife(1000);
	BulletParams.SetDamage(1);
	
	WeaponParam.FireRate = 1.f;
	WeaponParam.Radius = 4.f;
	WeaponParam.CountBullet = 2;
}

BWeapon::~BWeapon()
{
}

bool BWeapon::CheckTimeFire(const USceneComponent* BulletSpawn)
{
	const float time = BulletSpawn->GetWorld()->TimeSeconds; // UKismetSystemLibrary::GetGameTimeInSeconds(BulletSpawn);

	if (time < FireWait)
		return false;

	FireWait = time + WeaponParam.FireRate;

	return true;
}

void BWeapon::AddUpdate(const FWUpgrade& addFUpgrade)
{
	WeaponParam.FireRate += addFUpgrade.FireWait;
	WeaponParam.Radius += addFUpgrade.Radius;
	WeaponParam.CountBullet += addFUpgrade.CountBullet;

	if(WeaponParam.FireRate < .6f)
		WeaponParam.FireRate = .6f;

	if(WeaponParam.Radius > 90.f)
		WeaponParam.Radius = 90.f;

	if(WeaponParam.CountBullet > 6)
		WeaponParam.CountBullet = 6;
}

void BWeapon::Fire(const USceneComponent* BulletSpawn)
{
	if (Bullet == nullptr || WeaponParam.CountBullet < 1)
		return;
	
	AProjectile** bullets = Bullet->GetBullets(WeaponParam.CountBullet);

	if (bullets != nullptr)
	{  
		const FVector location = BulletSpawn->GetComponentLocation();
		const FRotator rotation = BulletSpawn->GetComponentRotation();
		
		const float startRadius = (WeaponParam.Radius * WeaponParam.CountBullet);
		const float deltaYaw = (startRadius / WeaponParam.CountBullet);
		float newYaw = rotation.Yaw - (startRadius / 2);
		const FRotator rotateBullet = BulletSpawn->GetForwardVector().Rotation();
		
		for (int32 i = 0; i < WeaponParam.CountBullet; i++)
		{ 
			const float newDeltaYaw = FMath::RandRange(newYaw, (newYaw + deltaYaw));
			const FRotator yawRotation(0.f, newDeltaYaw, 0.f);
			const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
			const float lagSpeed = FMath::RandRange(0.f, 900.f);

			newYaw += deltaYaw;

			AProjectile* bullet = bullets[i];
			
			bullet->SetDirection(direction, BulletParams.GetSpeed() - lagSpeed);
			bullet->SetActorLocation(location, false, nullptr, ETeleportType::None);
			bullet->SetActorRotation(rotateBullet, ETeleportType::None);
			bullet->SetWeapon(BulletParams);

			bullet->SetActive(true);
		}
	}
}
