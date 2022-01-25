#pragma once
#include "WeaponUpgrade.h"

class ItemDrop
{
	TSubclassOf<AWeaponUpgrade> TFireRate;
	TSubclassOf<AWeaponUpgrade> TBulletCount;

	UWorld* World;

	int32 Seed;

public:
	ItemDrop();

	void Initialize(UWorld* world);
	
	void Drop(const FVector position);
};
