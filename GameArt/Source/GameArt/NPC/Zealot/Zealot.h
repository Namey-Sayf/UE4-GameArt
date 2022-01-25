// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameArt/NPC/NPCCharacter.h"
#include "GameArt/NPC/Drone/GravityMovement.h"
#include "GameArt/Weapon/DBulletPool.h"

#include "Zealot.generated.h"

UCLASS()
class GAMEART_API AZealot : public ANPCCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZealot();

	virtual void BeginPlay() override;

protected:
	// Called when the game starts or when spawned
	virtual void PossessedBy(AController* NewController) override;

	void UpdateFire(float deltaTime);

private:
	UPROPERTY(Category = Movement, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UGravityMovement* Movement;

	UPROPERTY(BlueprintReadWrite, Category = Point, meta = (AllowPrivateAccess = "true"))
	USceneComponent* PWeapons;

	UPROPERTY(EditAnywhere, Category = Weapon)
	FWParams WeaponParam;
	
		float FireRate;

	UDBulletPool* BulletPool;

	float TimeFire;
	int32 CountBullet;
	
	typedef void (AZealot::*UpdateFunc)(float);
	UpdateFunc UpdFire;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetFire(bool isFire);
};

