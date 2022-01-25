// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameArt/Weapon/Damagable/ExcDamage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	UCharacterMovementComponent* const charapter = GetCharacterMovement();

	charapter->bOrientRotationToMovement = false; // Rotate character to moving direction
	charapter->bConstrainToPlane = true;
	charapter->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	WeaponTarget = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnLocation"));
	WeaponTarget->SetupAttachment(RootComponent);
	WeaponTarget->SetRelativeRotation(FRotator::ZeroRotator);
	WeaponTarget->SetRelativeLocation(FVector(50.f, 20.f, 30.f));

	WeaponController = CreateDefaultSubobject<UWeaponController>(TEXT("WController"));

	Health.SetHealth(101);
	Health.SetMaxHealth(111);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ChangeHealth();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFire);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	WeaponController->Initialize(WeaponTarget);
}

void APlayerCharacter::AddWeaponUpgrade(const FWUpgrade& upgrade)
{
	if (WeaponController)
		WeaponController->AddWeaponUpgrade(upgrade);
}

void APlayerCharacter::SetDamage(const FWParams& damage, const FVector& direction)
{
	ExcDamage::ApplyDamage(damage, Health);

	if (Health.GetHealth() == 0)
	{
		if (OnDeath.IsBound())
		{
			OnDeath.Broadcast(this);
		}
		else
		{
			MaxHealth();
		}
	}
	else
	{
		ChangeHealth();
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(FVector::RightVector, Value);
}

void APlayerCharacter::StartFire()
{
	if (WeaponController)
		WeaponController->SetFire(true);
}

void APlayerCharacter::StopFire()
{
	if (WeaponController)
		WeaponController->SetFire(false);
}

void APlayerCharacter::MaxHealth()
{
	Health.SetMaximum();

	ChangeHealth();
}

FORCEINLINE void APlayerCharacter::ChangeHealth()
{
	if (Health.GetHealth() > -1 && OnChangeHealth.IsBound())
		OnChangeHealth.Broadcast(Health);
}
