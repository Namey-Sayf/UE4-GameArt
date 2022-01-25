#include "ItemDrop.h"

ItemDrop::ItemDrop(): World(nullptr), Seed(90)
{
	const ConstructorHelpers::FClassFinder<AWeaponUpgrade> FireRate(
		TEXT("/Game/StarterContent/Blueprints/Item/UP_FireRate"));

	if (FireRate.Class != nullptr)
	{
		TFireRate = (FireRate.Class);
	}

	const ConstructorHelpers::FClassFinder<AWeaponUpgrade> BulletCount(
		TEXT("/Game/StarterContent/Blueprints/Item/UP_MoreBullet"));

	if (BulletCount.Class != nullptr)
	{
		TBulletCount = (BulletCount.Class);
	}
}

void ItemDrop::Initialize(UWorld* world)
{
	World = world;
}

void ItemDrop::Drop(const FVector position)
{
	if (World)
	{
		Seed += FMath::RandRange(0, 100);
		UE_LOG(LogTemp, Warning, TEXT(" -> Drop :  %d"), Seed);

		if (Seed > 99)
		{
			Seed = 0;
			
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			const TSubclassOf<AWeaponUpgrade> Item = FMath::RandRange(0, 1) ? TFireRate : TBulletCount;

			World->SpawnActor<AActor>(Item, position, FRotator::ZeroRotator, SpawnInfo);
		}
	}
}
