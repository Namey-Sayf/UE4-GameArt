// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameArt/Weapon/WeaponController.h"
#include "GameArt/Weapon/Damagable/Damagable.h"
#include "GameArt/Weapon/Damagable/LifeParams.h"
#include "GameArt/Weapon/Damagable/WParams.h"
#include "GameArt/Weapon/Damagable/WUpgrade.h"


#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

//DECLARE_EVENT_TwoParams(APlayerCharacter, DelegateTwoParams, int32, int32)

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegateTwoParams, int32, currentHealth, int32, maxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateLife, const FLifeParams&, Health);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateDeath, const AActor*, Player);

UCLASS(Blueprintable)
class GAMEART_API APlayerCharacter : public ACharacter, public IDamagable
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();
	
public:
	FDelegateLife OnChangeHealth;
	FDelegateDeath OnDeath;

	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
	FORCEINLINE FLifeParams GetHealth() const { return Health; }

	void AddWeaponUpgrade(const FWUpgrade& upgrade);

	virtual void SetDamage(const FWParams& damage, const FVector& direction) override;

	void MaxHealth();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	USceneComponent* WeaponTarget;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UWeaponController* WeaponController;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UDecalComponent* CursorToWorld;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float speed;

	FLifeParams Health;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void StartFire();
	void StopFire();

	void ChangeHealth();
};
