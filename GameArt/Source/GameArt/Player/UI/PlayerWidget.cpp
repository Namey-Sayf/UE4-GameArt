// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TWave)
		TWave->SetVisibility(ESlateVisibility::Hidden);

	TimeHide = 2.f;
}

void UPlayerWidget::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
{
	Super::NativeTick(MovieSceneBlends, InDeltaTime);

	if (TimeHide > 0)
	{
		TimeHide -= InDeltaTime;

		if (TimeHide < 0)
		{
			TWave->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UPlayerWidget::PrintWave(const FText& text, float time)
{
	TimeHide = time;

	TWave->SetVisibility(ESlateVisibility::Visible);
	TWave->SetText(text);
}

void UPlayerWidget::PrintCountEnemy(const FText& count)
{
	TLeftEnemy->SetText(count);
}

void UPlayerWidget::PrintHealth(const FText& tHealth, float phealth)
{
	PHealth->SetPercent(phealth);
	NHealth->SetText(tHealth);
}

void UPlayerWidget::PrintHealth(const FLifeParams& health)
{
	PHealth->SetPercent(static_cast<float>(health.GetHealth()) / health.GetMaxHealth());
	NHealth->SetText(FText::AsNumber(health.GetHealth()));
}
