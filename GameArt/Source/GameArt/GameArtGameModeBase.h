// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameArtyGameState.h"
#include "GameFramework/GameModeBase.h"
#include "NPC/Spawner.h"
#include "Weapon/DBulletPool.h"

#include "GameArtGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API AGameArtGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UDBulletPool NPCBulletPool;
	UDBulletPool PlayerBulletPool;

	ASpawner* NpcSpawner;
	AGameArtyGameState* GGameState;

	class AGPlayerController* GPlayer;
	ItemDrop* CItemDrop;

	FTimerHandle InOutHandle;

public:
	AGameArtGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes, meta = (DisplayName = "Spawner Class"))
	TSubclassOf<ASpawner> NpcSpawnerClass;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual APlayerController* SpawnPlayerControllerCommon(ENetRole InRemoteRole, FVector const& MovieSceneBlends,
	                                                       FRotator const& SpawnRotation,
	                                                       TSubclassOf<APlayerController>
	                                                       InPlayerControllerClass) override;

public:
	virtual void InitGameState() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void Destroyed() override;

	void NpcDeath();

	UDBulletPool* GetNPCBulletPool() { return &NPCBulletPool; };
	UDBulletPool* GetPlayerBulletPool() { return &PlayerBulletPool; };
	ASpawner* GetSpawner() { return NpcSpawner; };
	ItemDrop* GetItemDrop() { return CItemDrop; };

private:
	void TNextWave();
	void NextWave();
};
