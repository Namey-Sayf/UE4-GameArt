// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameArt/Weapon/Damagable/LifeParams.h"

#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

	float TimeHide;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* PHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TLeftEnemy;

	void PrintWave(const FText& text, float time = 2.f);

	void PrintCountEnemy(const FText& count);
	void PrintHealth(const FText& health, float phealth);

	void PrintHealth(const FLifeParams& health);

private:

};