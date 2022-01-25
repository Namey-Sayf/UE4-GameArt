#pragma once

#include "CoreMinimal.h"
#include "WUpgrade.generated.h"

USTRUCT(BlueprintType)
struct FWUpgrade
{
	GENERATED_BODY()

	FWUpgrade(): FWUpgrade(0.f, 0.f, 0)
	{
	}

	FWUpgrade(float fire, float rad, int32 count):
		FireWait(fire), Radius(rad), CountBullet(count)
	{
	}
	
	UPROPERTY(EditAnywhere)
	float FireWait;
	UPROPERTY(EditAnywhere)
	float Radius;
	UPROPERTY(EditAnywhere)
	int32 CountBullet;
};
