// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "Damagable/WParams.h"
#include "GameArt/NPC/Stalker/BTTask/BTT_StalkerMove.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Projectile.generated.h"

UCLASS()
class GAMEART_API AProjectile : public AActor
{
	GENERATED_BODY()

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

public:
	AProjectile();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	USphereComponent* GetCollisionComponent() const
	{
		return CollisionComponent;
	}

protected:
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, Category=Effect)
	UNiagaraSystem* DeathEffect;

	//UPROPERTY(VisibleAnywhere, Category=Weapon)
	FWParams Damage;

	float TimeLife;

public:
	FWParams GetWeapon() const { return Damage; }
	
	void SetWeapon(const FWParams& params)
	{
		Damage = params;
	}

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetActive(bool isActive);

	void SetDirection(FVector direction, float speed) const;
};
