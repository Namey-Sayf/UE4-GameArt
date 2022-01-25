// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"

#include "NiagaraFunctionLibrary.h"
#include "GameArt/Player/PlayerCharacter.h"
#include "GameArt/GameArtGameModeBase.h"
#include "GameArt/Weapon/Damagable/ExcDamage.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANPCCharacter::ANPCCharacter(): GGameMode(nullptr)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;

#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SpriteInfo.Category = TEXT("ID_Characters");
		ArrowComponent->SpriteInfo.DisplayName = FText::FromName(TEXT("NAME_Characters"));
		ArrowComponent->SetupAttachment(CapsuleComponent);
		ArrowComponent->bIsScreenSizeScaled = true;
	}
#endif // WITH_EDITORONLY_DATA
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	AGameArtGameModeBase* gameMode = Cast<AGameArtGameModeBase>(GetWorld()->GetAuthGameMode());
	GGameMode = gameMode;

	CItemDrop = gameMode->GetItemDrop();
}

void ANPCCharacter::SetDamage(const FWParams& param, const FVector& direction)
{
	ExcDamage::ApplyDamage(param, LifeParams);

	if (LifeParams.GetHealth() < 1)
	{
		CItemDrop->Drop(GetActorLocation());
		
		OnDeath(direction.Rotation(), DeathEffect);
	}
}

void ANPCCharacter::OnDeath(const FRotator& direction, UNiagaraSystem* effect)
{
	if (SoundDeath)
		UGameplayStatics::PlaySoundAtLocation(this, SoundDeath, GetActorLocation());

	if (effect)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), effect, GetActorLocation(), direction);

	if (GGameMode)
		GGameMode->NpcDeath();

	Destroy();
}
