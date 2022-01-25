#include "DBulletPool.h"
#include "Projectile.h"

UDBulletPool::UDBulletPool() : Bulls(nullptr), World(nullptr), CurrentIndex(0), CountUseItem(0), CountItem(0),
                               LengthArr(0)
{
}

UDBulletPool::~UDBulletPool()
{
	if (Bulls)
		delete [] Bulls;
}

void UDBulletPool::InitializeBullet(const TSubclassOf<AProjectile>& bullet) noexcept
{
	StackBullet.Reserve(CountItem);

	if (bullet != nullptr)
	{
		Bullet = bullet;
	}
}

void UDBulletPool::ReturnBullet()
{
	if (CountUseItem > 0)
	{
		CountUseItem--;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("   -> CountUseItem < 0"));
	}
}

void UDBulletPool::AddWorld(UWorld* const world)
{
	World = world;

	CreateBullet(10);
}

AProjectile** UDBulletPool::GerArray(int32 length)
{
	if (LengthArr < length)
	{
		if (Bulls)
			delete [] Bulls;

		LengthArr = length + 10;

		Bulls = new AProjectile*[LengthArr];

		CreateBullet(10);
	}

	return Bulls;
}

void UDBulletPool::CreateBullet(const int32 count)
{
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("   -> World is NULL"));
		return;
	}

	if (!Bullet)
	{
		UE_LOG(LogTemp, Error, TEXT("   -> Bullet is NULL"));
		return;
	}

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 i = 0; i < count; i++, CountItem++)
	{
		AProjectile* bull = World->SpawnActor<AProjectile>(Bullet, FVector::ZeroVector, FRotator::ZeroRotator,
		                                                   SpawnInfo);
		bull->SetActive(false);

		StackBullet.Add(bull);
	}
}

AProjectile* UDBulletPool::GetBullet()
{
	AProjectile* bull = nullptr;

	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("   -> World is NULL"));
		return nullptr;
	}

	if (StackBullet.Num() > 0)
	{
		bull = StackBullet[CurrentIndex];

		CurrentIndex = (CurrentIndex + 1) % CountItem;

		CountUseItem++;
		return bull;
	}

	return nullptr;
}

AProjectile** UDBulletPool::GetBullets(int32 count)
{
	if (count < 1)
		return nullptr;

	if (!World)
	{
		UE_LOG(LogTemp, Log, TEXT("   -> World is NULL"));
		return nullptr;
	}

	AProjectile** bull = nullptr;

	if (StackBullet.Num() >= count)
	{
		bull = GerArray(count);
		const int32 COUNT = StackBullet.Num();

		for (int32 i = 0; i < count; i++)
		{
			const int32 index = (CurrentIndex + i) % COUNT;
			bull[i] = StackBullet[index];
		}

		CurrentIndex = (CurrentIndex + count) % CountItem;
		CountUseItem++;
	}

	return bull;
}
