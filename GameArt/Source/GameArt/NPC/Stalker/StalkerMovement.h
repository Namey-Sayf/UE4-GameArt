#pragma once

#include "CoreMinimal.h"
//#include "AIController.h"

#include "GameFramework/PawnMovementComponent.h"

#include "StalkerMovement.generated.h"

enum StateMove: int8
{
	Stalker_Stay,
	Stalker_Walk,
	Stalker_Strafing,
};

class AStalkerAIController;
/**
* 
*/
UCLASS()
class GAMEART_API UStalkerMovement : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	UStalkerMovement();
	
	virtual void BeginPlay() override;

	void AddDirectionMove(const FVector direction);

	void SwitchState(const StateMove state);
	
	StateMove GetState() const { return CurrentState; }
	
private:
	UPROPERTY(EditAnywhere, Category = Movement)
	float Friction;

	UPROPERTY(EditAnywhere, Category = Movement)
	float WalkSpeed;

	float Speed;
	float TimeMove;
	
	StateMove CurrentState;

	AStalkerAIController* controller;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
