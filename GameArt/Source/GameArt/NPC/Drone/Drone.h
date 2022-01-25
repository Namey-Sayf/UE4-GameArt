// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneAIController.h"

#include "GravityMovement.h"
#include "GameArt/NPC/NPCCharacter.h"

#include "Drone.generated.h"

UCLASS()
class GAMEART_API ADrone : public ANPCCharacter
{
	GENERATED_BODY()

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& Hit);

public:
	// Sets default values for this character's properties
	ADrone();

private:
	UPROPERTY(EditAnywhere, Category = Weapon)
	FWParams Damage;

	UPROPERTY(EditAnywhere, Category = Effects)
	UNiagaraSystem* ExplosionEffect;

	UPROPERTY(Category = Movement, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UGravityMovement* Movement;

protected:
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
};
