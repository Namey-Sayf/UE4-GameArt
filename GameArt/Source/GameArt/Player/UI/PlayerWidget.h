// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameArt/Weapon/Damagable/LifeParams.h"

#include "PlayerWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(TickDelgate, float)
/**
 * 
 */
UCLASS()
class GAMEART_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
	bool IsDowningHealth;
	float TimeHide;
	float TimeHealthHide;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	FORCEINLINE void RunDownHealth();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* PHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* PHealthDowning;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TLeftEnemy;

	void PrintWave(const FText& text, float time = 2.f);

	void PrintCountEnemy(const FText& count) const;

	void PrintHealth(const FText& health, float Phealth);

	void PrintHealth(const FLifeParams& health);

private:
	TickDelgate UpdateEvents;

	void UpdHideWave(float DeltaTime);
	FDelegateHandle UpdHideWaveHandle;

	void UpdWownHealth(float DeltaTime);
	FDelegateHandle UpdWownHealthHandle;
};
