#pragma once

#include "CoreMinimal.h"

class AProjectile;
/**
 * 
 */
class UDBulletPool
{
	TSubclassOf<AProjectile> Bullet;

	TArray<AProjectile*> StackBullet;
	AProjectile** Bulls;

	UWorld* World;

	int32 CurrentIndex;
	int32 CountUseItem;
	int32 CountItem;

	int32 LengthArr;

	FORCEINLINE AProjectile** GerArray(int32 length);

public:
	UDBulletPool();
	~UDBulletPool();

	void InitializeBullet(const TSubclassOf<AProjectile>& bullet) noexcept;

	void ReturnBullet();

	void CreateBullet(const int32 count);

	void AddWorld(UWorld* const world);

	AProjectile* GetBullet();

	//bool GetBullets(TArray<AProjectile*>& arr, int32 count);
	AProjectile** GetBullets(int32 count);
};
