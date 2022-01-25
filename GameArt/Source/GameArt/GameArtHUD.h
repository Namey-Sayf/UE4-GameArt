// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/HUD.h"
#include "Player/UI/PlayerWidget.h"

#include "GameArtHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API AGameArtHUD : public AHUD
{
	GENERATED_BODY()

	TSubclassOf<UPlayerWidget> PlayerWidget;

public:
	AGameArtHUD();

protected:
	virtual void BeginPlay() override;

public:
	UPlayerWidget* GetCurrenWidget() const { return CurrentWidget; };
	
	void PrintHealth(const FLifeParams& health);
	void PrintWave(int32 count);
	void PrintCountEnemy(int32 count);
	void PrintWave(const FText& text);
	void PrintCountEnemy(const FText& count);

private:
	UPlayerWidget* CurrentWidget;
};
