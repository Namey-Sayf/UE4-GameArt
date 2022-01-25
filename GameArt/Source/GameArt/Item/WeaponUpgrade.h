// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Components/BoxComponent.h"
#include "GameArt/Weapon/Damagable/WUpgrade.h"

#include "GameFramework/Actor.h"
#include "WeaponUpgrade.generated.h"

class APlayerCharacter;

UCLASS()
class GAMEART_API AWeaponUpgrade : public AActor
{
	GENERATED_BODY()

private:
	// declare overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	FWUpgrade Upgrade;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UNiagaraSystem* TakeEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* SoundTake;

	float LifeTime;

public:
	// Sets default values for this actor's properties
	AWeaponUpgrade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	// Called every frame
};
