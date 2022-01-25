#pragma once

#include "CoreMinimal.h"
#include "DBulletPool.h"
#include "Damagable/WParams.h"

#include "Damagable/WUpgrade.h"

struct FWeapon
{
	FWeapon(): FWeapon(1.f, 5.f, 2)
	{
	}

	FWeapon(float fire, float rad, int32 count):
		FireRate(fire), Radius(rad), CountBullet(count)
	{
	}

	float FireRate;
	float Radius;
	int32 CountBullet;
};

class BWeapon //: public UObject
{
public:
	BWeapon();
	~BWeapon();

private:
	FWeapon WeaponParam;
	FWParams BulletParams;
	float FireWait;
	
	UDBulletPool* Bullet;

public:
	bool CheckTimeFire(const USceneComponent* BulletSpawn);

	// Called when the game starts or when spawned
	void Fire(const USceneComponent* BulletSpawn);
	
	void AddUpdate(const FWUpgrade& BulletSpawn);
	
	void AddBullet(UDBulletPool* bullet)
	{
		Bullet = bullet;
	}
};
