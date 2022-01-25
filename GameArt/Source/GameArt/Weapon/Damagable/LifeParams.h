#pragma once
#include "CoreMinimal.h"
#include "LifeParams.generated.h"

USTRUCT()
struct FLifeParams
{
	GENERATED_BODY()

	FLifeParams() : FLifeParams(1)
	{
	}

	FLifeParams(int32 baseHealth) :
		MaxHealth(baseHealth), Health(baseHealth)
	{
	}

private:
	UPROPERTY(EditAnywhere)
	int32 MaxHealth;
	UPROPERTY(EditAnywhere)
	int32 Health;

public:
	int32 GetHealth() const noexcept { return Health; }
	int32 GetMaxHealth() const noexcept { return MaxHealth; }

	void SetMaxHealth(int32 health) noexcept
	{
		MaxHealth = health < 0 ? 0 : health;
	}

	void SetHealth(int32 health) noexcept
	{
		Health = health < 0 ? 0 : health;
	}

	void SetMaximum()
	{
		Health = MaxHealth;
	}
};
