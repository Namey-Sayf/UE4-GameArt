// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"

#include "GameArt/GameArtHUD.h"


#include "GameFramework/PlayerController.h"
#include "GPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEART_API AGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGPlayerController();

	FORCEINLINE APlayerCharacter* GetPlayer() const { return Cast<APlayerCharacter>(GetPawn()); }

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	AGameArtHUD* ArtHud;
	APlayerCharacter* ArtPlayer;

	virtual void BeginPlay() override;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void ChangeHealth(const FLifeParams& life);
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	//	void GetWorldPositionCursor();
	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	/* UI Calls*/
public:
	void PrintHealth() const;
	void PrintWave(const int32 count) const;
	void PrintCountEnemy(const int32 count) const;
};
