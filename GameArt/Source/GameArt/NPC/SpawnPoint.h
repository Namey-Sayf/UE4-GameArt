// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCCharacter.h"

#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UENUM()
enum ENpcType { None, Drone, Zealot, Stalker };

UCLASS()
class GAMEART_API ASpawnPoint : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = NpcSpawn, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ENpcType> Type;

	UWorld* CWorld;
	
#if WITH_EDITORONLY_DATA
	UArrowComponent* ArrowComponent;
#endif
	
public:
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Spawn(const TSubclassOf<ANPCCharacter>& Npc) const;
};
