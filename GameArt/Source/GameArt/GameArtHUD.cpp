// Fill out your copyright notice in the Description page of Project Settings.


#include "GameArtHUD.h"

#include "Blueprint/UserWidget.h"

AGameArtHUD::AGameArtHUD() : CurrentWidget(nullptr)
{
	static ConstructorHelpers::FClassFinder<UPlayerWidget> PlayerWidgetBPClass(
		TEXT("/Game/StarterContent/Blueprints/BPlayerWidget"));

	if (PlayerWidgetBPClass.Class != nullptr)
	{
		PlayerWidget = PlayerWidgetBPClass.Class;
	}
}

void AGameArtHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerWidget)
	{
		CurrentWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidget);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AGameArtHUD::PrintHealth(const FLifeParams& health)
{
	if (CurrentWidget)
	{
		const float ph = static_cast<float>(health.GetHealth()) / health.GetMaxHealth();
		CurrentWidget->PrintHealth(FText::AsNumber(health.GetHealth()), ph);
	}
}

void AGameArtHUD::PrintWave(const int32 count)
{
	if (CurrentWidget)
	{
		const auto textWave = FText::Format(
			NSLOCTEXT("0", "11", "Wave : {0}"), FText::AsNumber(count));
		CurrentWidget->PrintWave(textWave, 4.f);
	}
}

void AGameArtHUD::PrintCountEnemy(const int32 count)
{
	if (CurrentWidget)
	{
		const auto textCount = FText::Format(
			NSLOCTEXT("0", "11", "Enemy : {0}"), FText::AsNumber(count));
		CurrentWidget->PrintCountEnemy(textCount);
	}
}
