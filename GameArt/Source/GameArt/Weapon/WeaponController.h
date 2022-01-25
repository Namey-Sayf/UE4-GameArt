#pragma once

#include "CoreMinimal.h"
#include "DBulletPool.h"
#include "Weapon.h"

#include "WeaponController.generated.h"

UCLASS(ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class GAMEART_API UWeaponController : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* SoundWeaponFire;
	
	UDBulletPool* BulletPool;

	BWeapon* CurrentWeapon;

	TArray<BWeapon*> BagWeapons;

	USceneComponent* BulletSpawnLocation;

	bool IsFire;

	void InitWeapon();

	void FireGun();

public:
	UWeaponController();

protected:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void DestroyComponent(bool bPromoteChildren) override;

public:
	void SetFire(bool isFire);

	void Initialize(USceneComponent* bSpawn);

	void AddWeaponUpgrade(const FWUpgrade& weaponUpgrade);
};
