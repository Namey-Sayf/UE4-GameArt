// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"

// Sets default values
ASpawner::ASpawner() : CurrentWave(0)
{
	const ConstructorHelpers::FClassFinder<ANPCCharacter> NpcDrone(
		TEXT("/Game/StarterContent/Blueprints/NPC/BDrone"));

	if (NpcDrone.Class != nullptr)
	{
		TDrone = (NpcDrone.Class);
	}

	const ConstructorHelpers::FClassFinder<ANPCCharacter> NpcZealot(
		TEXT("/Game/StarterContent/Blueprints/NPC/BZealot"));

	if (NpcZealot.Class != nullptr)
	{
		TZealot = (NpcZealot.Class);
	}

	const ConstructorHelpers::FClassFinder<ANPCCharacter> NpcStalker(
		TEXT("/Game/StarterContent/Blueprints/NPC/BStalker"));

	if (NpcStalker.Class != nullptr)
	{
		TStalker = (NpcStalker.Class);
	}
}

void ASpawner::InitWave()
{
	Wave.AddNpc(2.f, 0.2f, TDrone);
	Wave.AddNpc(0.8f, 0.2f, TZealot);
	Wave.AddNpc(0.6f, 0.2f, TStalker);
}

void ASpawner::AddSpawnPoint(ASpawnPoint* Point, ENpcType Type)
{
	SPoints.Add(Point);
}

int32 ASpawner::NextWave()
{
	CurrentWave++;

	int32 count = 0;
	const TArray<FInfoWave*> Info = Wave.GetInfo();

	for (FInfoWave* WInfo : Info)
	{
		const int32 c = WInfo->Count();

		if (c > 0)
		{
			count += c;
			SpawnNpc(SPoints, WInfo->TChar, c);
		}
		//WInfo.Up();
	}

	if (CurrentWave < 5)
		Wave.Upgrade();

	return count > 0 ? count : -1;
}

void ASpawner::SpawnNpc(TArray<ASpawnPoint*>& spawn, TSubclassOf<ANPCCharacter> npc, int32 count)
{
	const int32 LENGTH = spawn.Num();

	if (LENGTH > 0)
	{
		const int32 RandPos = FMath::RandRange(0, 8);

		for (int i = 0; i < count; i++)
		{
			const int32 index = (i + RandPos) % LENGTH;

			spawn[(index)]->Spawn(npc);
		}
	}
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	InitWave();
}
