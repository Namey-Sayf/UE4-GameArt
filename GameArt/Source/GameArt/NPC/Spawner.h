// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCCharacter.h"
#include "SpawnPoint.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

struct FInfoWave
{
	FInfoWave(float count, float up, const TSubclassOf<ANPCCharacter>& AChar) :
		Upgrade(up), CountUpgrade(count), TChar(AChar)
	{
	}

	FInfoWave(const FInfoWave& w) : Upgrade(w.Upgrade), CountUpgrade(w.CountUpgrade), TChar(w.TChar)
	{
		UE_LOG(LogTemp, Warning, TEXT(" -> FInfoWave COPY"));
	}

	// FInfoWave(const FInfoWave&) = delete;
	// FInfoWave& operator=(const FInfoWave&) = delete;

	float Upgrade;
	float CountUpgrade;

	TSubclassOf<ANPCCharacter> TChar;

	void Up()
	{
		CountUpgrade += Upgrade;
	}

	FORCEINLINE const int32 Count() const { return static_cast<int32>(CountUpgrade); }
};

struct FWave
{
private:
	TArray<FInfoWave*> Info;

public:
	FWave()
	{
		UE_LOG(LogTemp, Warning, TEXT(" -> FWave DEF"));
	};

	FWave(const FWave& w) : Info(w.Info)
	{
		UE_LOG(LogTemp, Warning, TEXT(" -> FWave COPY"));
	}

	~FWave()
	{
		if (Info.Num() > 0)
		{
			for (const FInfoWave* item : Info)
			{
				if (item)
					delete item;
			}
		}
	}

	void Upgrade()
	{
		for (FInfoWave* item : Info)
		{
			item->Up();
		}
	}

	void AddNpc(float count, float update, TSubclassOf<ANPCCharacter>& npcChar)
	{
		auto info = new FInfoWave(count, update, npcChar);
		Info.Add(info);
	}

	const TArray<FInfoWave*>& GetInfo() const { return Info; }
};

UCLASS()
class GAMEART_API ASpawner : public AActor
{
	GENERATED_BODY()

	TArray<ASpawnPoint*> SPoints;

	TSubclassOf<ANPCCharacter> TDrone;
	TSubclassOf<ANPCCharacter> TStalker;
	TSubclassOf<ANPCCharacter> TZealot;

	int32 CurrentWave;

	FWave Wave;

public:
	// Sets default values for this actor's properties
	ASpawner();

	void AddSpawnPoint(ASpawnPoint* Point, ENpcType Type);

	int32 NextWave();

	int32 GetCurrentWave() const { return CurrentWave; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitWave();
	void SpawnNpc(TArray<ASpawnPoint*>& spawn, TSubclassOf<ANPCCharacter> npc, int32 count);

public:
	// Called every frame
};
