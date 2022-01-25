// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponUpgrade.h"

#include "NiagaraFunctionLibrary.h"
#include "GameArt/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponUpgrade::AWeaponUpgrade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision radius.
	CollisionComponent->InitBoxExtent(FVector(50, 50, 50));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Item"));

	RootComponent = CollisionComponent;
}

// Called when the game starts or when spawned
void AWeaponUpgrade::BeginPlay()
{
	Super::BeginPlay();

	LifeTime = 20.f;
}

void AWeaponUpgrade::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeaponUpgrade::OnOverlapBegin);
	}
}

void AWeaponUpgrade::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	LifeTime -= DeltaSeconds;

	if (LifeTime <= 0)
	{
		Destroy();
	}
}

void AWeaponUpgrade::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);

	if (player)
	{
		player->AddWeaponUpgrade(Upgrade);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TakeEffect, GetActorLocation(),
			FRotator::ZeroRotator);
		if (SoundTake)
			UGameplayStatics::PlaySound2D(this, SoundTake);

		Destroy();
	}
}
