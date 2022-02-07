// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TWave)
		TWave->SetVisibility(ESlateVisibility::Hidden);

	TimeHide = 0.f;
}

void UPlayerWidget::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
{
	Super::NativeTick(MovieSceneBlends, InDeltaTime);

	if (UpdateEvents.IsBound())
	{
		UpdateEvents.Broadcast(InDeltaTime);
	}
}

void UPlayerWidget::PrintHealth(const FText& tHealth, float Phealth)
{
	RunDownHealth();

	PHealth->SetPercent(Phealth);
	NHealth->SetText(tHealth);
}

void UPlayerWidget::PrintHealth(const FLifeParams& health)
{
	RunDownHealth();

	PHealth->SetPercent(static_cast<float>(health.GetHealth()) / health.GetMaxHealth());
	NHealth->SetText(FText::AsNumber(health.GetHealth()));
}

void UPlayerWidget::PrintWave(const FText& text, float time)
{
	TWave->SetText(text);

	if (TimeHide <= 0)
	{
		TWave->SetVisibility(ESlateVisibility::Visible);
		UpdHideWaveHandle = UpdateEvents.AddUObject(this, &UPlayerWidget::UpdHideWave);
	}

	TimeHide = time;
}

void UPlayerWidget::PrintCountEnemy(const FText& count) const
{
	TLeftEnemy->SetText(count);
}

void UPlayerWidget::RunDownHealth()
{
	if (!IsDowningHealth)
	{
		TimeHealthHide = 2.f;
		UpdWownHealthHandle = UpdateEvents.AddUObject(this, &UPlayerWidget::UpdWownHealth);
	}

	if (PHealthDowning->Percent < PHealth->Percent)
	{
		PHealthDowning->SetPercent(1.f);
	}

	IsDowningHealth = true;
}

void UPlayerWidget::UpdHideWave(float DeltaTime)
{
	if (TimeHide > 0)
	{
		TimeHide -= DeltaTime;

		if (TimeHide < 0)
		{
			UpdateEvents.Remove(UpdHideWaveHandle);
			TWave->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UPlayerWidget::UpdWownHealth(float DeltaTime)
{
	if (PHealthDowning)
	{
		TimeHealthHide -= DeltaTime;

		if (TimeHealthHide > 0)
			return;

		float newPercent = PHealthDowning->Percent - (.1f * DeltaTime);

		if (newPercent <= PHealth->Percent)
		{
			UpdateEvents.Remove(UpdWownHealthHandle);
			newPercent = PHealth->Percent;
			IsDowningHealth = false;
		}

		PHealthDowning->SetPercent(newPercent);
	}
}
