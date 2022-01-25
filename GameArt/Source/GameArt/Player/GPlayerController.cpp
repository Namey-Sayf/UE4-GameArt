// Fill out your copyright notice in the Description page of Project Settings.


#include "GPlayerController.h"

#include "PlayerCharacter.h"

AGPlayerController::AGPlayerController() : ArtHud(nullptr)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ArtHud = Cast<AGameArtHUD>(GetHUD());
}

void AGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	MoveToMouseCursor();
}

void AGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &ADomeDownPlayerController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &ADomeDownPlayerController::OnSetDestinationReleased);

	// support touch devices 
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ADomeDownPlayerController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ADomeDownPlayerController::MoveToTouchLocation);

	//InputComponent->BindAction("ResetVR", IE_Pressed, this, &ADomeDownPlayerController::OnResetVR);
}

void AGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ArtPlayer = Cast<APlayerCharacter>(InPawn);

	if (ArtPlayer)
	{
		ArtPlayer->OnChangeHealth.AddDynamic(this, &AGPlayerController::ChangeHealth);
	}
}

void AGPlayerController::ChangeHealth(const FLifeParams& life)
{
	if (ArtHud)
	{
		ArtHud->PrintHealth(life);
	}
}

void AGPlayerController::OnResetVR()
{
	//UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AGPlayerController::MoveToMouseCursor()
{
	ACharacter* character = GetCharacter();

	if (character)
	{
		FHitResult Hitc;
		bool bHit = GetHitResultUnderCursor(ECC_Visibility, false, Hitc);

		FVector v = Hitc.Location - character->GetActorLocation();
		FRotator lookAtRotator = v.Rotation();
		//FRotator lookAtRotator = FRotationMatrix::MakeFromX(v).Rotator();
		lookAtRotator.Pitch = 0;
		lookAtRotator.Roll = 0;

		character->SetActorRotation(lookAtRotator);
	}

	return;
}

void AGPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AGPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	return;
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AGPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AGPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AGPlayerController::PrintHealth() const
{
	if (ArtHud && ArtPlayer)
	{
		ArtHud->PrintHealth(ArtPlayer->GetHealth());
	}
}

void AGPlayerController::PrintWave(const int32 count) const
{
	if (ArtHud)
	{
		ArtHud->PrintWave(count);
	}
}

void AGPlayerController::PrintCountEnemy(const int32 count) const
{
	if (ArtHud)
	{
		ArtHud->PrintCountEnemy(count);
	}
}
