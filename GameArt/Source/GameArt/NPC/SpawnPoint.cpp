// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"

#include "GameArt/GameArtGameModeBase.h"

// Sets default values
ASpawnPoint::ASpawnPoint() : CWorld(nullptr)
{
#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SpriteInfo.Category = TEXT("ID_Characters");
		ArrowComponent->SpriteInfo.DisplayName = FText::FromName(TEXT("NAME_Characters"));
		ArrowComponent->SetupAttachment(RootComponent);
		ArrowComponent->bIsScreenSizeScaled = true;
	}
#endif // WITH_EDITORONLY_DATA
}

void ASpawnPoint::Spawn(const TSubclassOf<ANPCCharacter>& Npc) const
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CWorld->SpawnActor<AActor>(Npc, GetActorLocation(), GetActorRotation(), SpawnInfo);
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	CWorld = GetWorld();

	AGameArtGameModeBase* gameMode = Cast<AGameArtGameModeBase>(CWorld->GetAuthGameMode());
	const auto Spawner = gameMode->GetSpawner();

	if (Spawner)
		Spawner->AddSpawnPoint(this, Type.GetValue());
}
