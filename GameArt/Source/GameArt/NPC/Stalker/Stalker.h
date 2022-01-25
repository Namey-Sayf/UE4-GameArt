// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "StalkerMovement.h"
#include "GameArt/NPC/NPCCharacter.h"
#include "GameArt/Weapon/DBulletPool.h"

#include "Stalker.generated.h"

class UStalkerMovement;
/**
 * 
 */
UCLASS()
class GAMEART_API AStalker : public ANPCCharacter
{
	GENERATED_BODY()

public:
	AStalker();

protected:
	virtual void Tick(float DeltaTime) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Movement, meta=(AllowPrivateAccess = "true"))
	UStalkerMovement* Movement;

	UPROPERTY(VisibleAnywhere, Category = Point, meta = (AllowPrivateAccess = "true"))
	USceneComponent* PWeapons;

	UPROPERTY(EditAnywhere, Category = Weapon)
	FWParams WeaponParam;
	
	float FireRate;

	UDBulletPool* BulletPool;

	float TimeFire;

	typedef void (AStalker::*UpdateFunc)(float);
	UpdateFunc UpdFire;

	void UpdateFire(float deltaTime);

public:
	void SetFire(bool isFire);
};
