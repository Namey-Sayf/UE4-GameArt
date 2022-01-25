// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NiagaraSystem.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "GameArt/Item/ItemDrop.h"
#include "GameArt/Weapon/Damagable/Damagable.h"
#include "GameArt/Weapon/Damagable/LifeParams.h"

#include "NPCCharacter.generated.h"

UCLASS()
class GAMEART_API ANPCCharacter : public APawn, public IDamagable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();
	
protected:
	UPROPERTY(EditAnywhere, Category = "Effects")
	UNiagaraSystem* DeathEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* SoundDeath;

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, Category = Health)
	FLifeParams LifeParams;

	class AGameArtGameModeBase* GGameMode;

	ItemDrop* CItemDrop;

#if WITH_EDITORONLY_DATA
	UArrowComponent* ArrowComponent;
#endif // WITH_EDITORONLY_DATA

	virtual void BeginPlay() override;
	
	virtual void SetDamage(const FWParams& damage, const FVector& direction) override;

	virtual void OnDeath(const FRotator& direction, UNiagaraSystem* effect);
};
