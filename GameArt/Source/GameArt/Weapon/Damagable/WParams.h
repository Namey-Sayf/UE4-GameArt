#pragma once

#include "CoreMinimal.h"
#include "WParams.generated.h"

USTRUCT(BlueprintType)
struct FWParams
{
	GENERATED_BODY()

	FWParams() : FWParams(1, 400, 2000.f, 1.f)
	{
	}

	FWParams(int32 damage, int32 lengthLife, float speed, float fireRate):
		Damage(damage), LengthLife(lengthLife), Speed(speed)
	{
	}

private: 
	UPROPERTY(EditAnywhere)
	int32 Damage;

	UPROPERTY(EditAnywhere)
	int32 LengthLife;
	
	UPROPERTY(EditAnywhere)
	float Speed;

public:
	FORCEINLINE int32 GetDamage() const noexcept { return Damage; }
	FORCEINLINE float GetSpeed() const noexcept { return Speed; }
	FORCEINLINE float GetLengthLife() const noexcept { return LengthLife; }
	FORCEINLINE float GetLifeTime() const noexcept { return LengthLife / Speed; }

	FORCEINLINE void SetLengthLife(float length) noexcept { LengthLife = length; }
	FORCEINLINE void SetSpeed(float speed) noexcept { Speed = speed; }
	FORCEINLINE void SetDamage(int32 damage) noexcept { Damage = damage; }
};
