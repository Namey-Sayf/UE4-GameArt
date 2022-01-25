#include "WeaponController.h"

#include <memory>

#include "GameArt/GameArtGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UWeaponController::UWeaponController()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponController::InitializeComponent()
{
	Super::InitializeComponent();
}

void UWeaponController::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);
	
	if (IsFire)	
	{	                   
		if (CurrentWeapon)	
		{                 
			FireGun();
		}
		else
		{       
			IsFire = false;
		}
	}
}

void UWeaponController::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);

	if (CurrentWeapon != nullptr)
		delete CurrentWeapon;
}

void UWeaponController::SetFire(bool isFire)
{
	IsFire = isFire;
	
	if (isFire)
	{
		FireGun();
	}
}

void UWeaponController::InitWeapon()
{
	CurrentWeapon = new BWeapon();

	if (CurrentWeapon)
	{
		AGameArtGameModeBase* gameMode = Cast<AGameArtGameModeBase>(GetWorld()->GetAuthGameMode());

		BulletPool = gameMode->GetPlayerBulletPool();
		CurrentWeapon->AddBullet(BulletPool);
	}
}

void UWeaponController::FireGun()
{                         
	if (CurrentWeapon->CheckTimeFire(BulletSpawnLocation))
	{                                     
		CurrentWeapon->Fire(BulletSpawnLocation);

		if (SoundWeaponFire)
			UGameplayStatics::PlaySound2D(this, SoundWeaponFire);
	}
}

void UWeaponController::Initialize(USceneComponent* bSpawn)
{
	BulletSpawnLocation = bSpawn;
	InitWeapon();
}

void UWeaponController::AddWeaponUpgrade(const FWUpgrade& weaponUpgrade)
{
	if (CurrentWeapon)
		CurrentWeapon->AddUpdate(weaponUpgrade);
}
