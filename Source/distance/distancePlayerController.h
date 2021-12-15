// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "distancePlayerController.generated.h"

UENUM()
enum class EControlMode : uint8
{
	AimControlMode = 0,
	InventoryControlMode = 1,
};

UCLASS()
class AdistancePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AdistancePlayerController();

	FSimpleMulticastDelegate OnMouseButtonUp;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	EControlMode MouseControlMode;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	/** Change mouse control between movement/aim and inventory management **/
	void SwitchMouseControlMode();

	//
	void OnLeftMouseButtonUp();

};


