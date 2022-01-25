// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameArtGameModeBase.h"
#include "GameArtyGameState.h"
#include "GameFramework/PlayerState.h"
#include "Player/GPlayerController.h"

AGameArtGameModeBase::AGameArtGameModeBase() : NpcSpawner(nullptr)
{
	HUDClass = AGameArtHUD::StaticClass();
	GameStateClass = AGameArtyGameState::StaticClass();
	PlayerControllerClass = AGPlayerController::StaticClass();

	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
	// 	TEXT("/Game/StarterContent/Blueprints/BPlayerCharacter"));
	//
	// if (PlayerPawnBPClass.Class != nullptr)
	// {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }

	const ConstructorHelpers::FClassFinder<AProjectile> PlayerBullet(
		TEXT("/Game/StarterContent/Blueprints/Bullet/BProjectile"));

	if (PlayerBullet.Class != nullptr)
	{
		PlayerBulletPool.InitializeBullet(PlayerBullet.Class);
	}

	const ConstructorHelpers::FClassFinder<AProjectile> NPCBullet(
		TEXT("/Game/StarterContent/Blueprints/Bullet/BEnemyProjectile"));

	if (NPCBullet.Class != nullptr)
	{
		NPCBulletPool.InitializeBullet(NPCBullet.Class);
	}

	CItemDrop = new ItemDrop();
}

void AGameArtGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TNextWave();
}

void AGameArtGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

APlayerController* AGameArtGameModeBase::SpawnPlayerControllerCommon(ENetRole InRemoteRole,
                                                                     FVector const& MovieSceneBlends,
                                                                     FRotator const& SpawnRotation,
                                                                     TSubclassOf<APlayerController>
                                                                     InPlayerControllerClass)
{
	const auto control = Super::SpawnPlayerControllerCommon(InRemoteRole, MovieSceneBlends, SpawnRotation,
	                                                        InPlayerControllerClass);
	GPlayer = Cast<AGPlayerController>(control);

	return control;
}

void AGameArtGameModeBase::InitGameState()
{
	Super::InitGameState();

	GGameState = Cast<AGameArtyGameState>(GameState);
	if (GGameState == nullptr)
		UE_LOG(LogTemp, Error, TEXT(" -> GGameState  fail!"));
}

void AGameArtGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	const auto Wrold = GetWorld();

	PlayerBulletPool.AddWorld(Wrold);
	NPCBulletPool.AddWorld(Wrold);

	if(NpcSpawnerClass)
	{
		NpcSpawner = Wrold->SpawnActor<ASpawner>(NpcSpawnerClass);
	}
	else
	{
		NpcSpawner = Wrold->SpawnActor<ASpawner>();
	}
	
	if (CItemDrop)
		CItemDrop->Initialize(Wrold);
}

void AGameArtGameModeBase::Destroyed()
{
	Super::Destroyed();

	if (CItemDrop)
		delete CItemDrop;
}

void AGameArtGameModeBase::NpcDeath()
{
	if (NpcSpawner && GGameState)
	{
		GGameState->CountNpcLife--;

		if (GGameState->CountNpcLife == 0)
		{
			TNextWave();
		}

		if (GPlayer)
		{
			GPlayer->PrintCountEnemy(GGameState->CountNpcLife);
		}
	}
}

void AGameArtGameModeBase::TNextWave()
{
	if (NpcSpawner && GGameState)
	{
		GetWorldTimerManager().SetTimer(InOutHandle, this, &AGameArtGameModeBase::NextWave, 4.0f, false, 1.0f);
	}
}

void AGameArtGameModeBase::NextWave()
{
	if (NpcSpawner && GGameState)
	{
		const int32 count = NpcSpawner->NextWave();

		GGameState->SetCountNpc(count);

		if (GPlayer)
		{
			GPlayer->PrintCountEnemy(count);
			GPlayer->PrintWave(NpcSpawner->GetCurrentWave());
		}
	}
}
