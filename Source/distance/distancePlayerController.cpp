// Copyright Epic Games, Inc. All Rights Reserved.

#include "distancePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "distanceCharacter.h"
#include "Engine/World.h"

AdistancePlayerController::AdistancePlayerController()
{
	bShowMouseCursor = true;
	
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	MouseControlMode = EControlMode::AimControlMode;

}

void AdistancePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	bEnableClickEvents = true;  // might need to turn it off in case it will screw something up

	if (MouseControlMode == EControlMode::AimControlMode)
	{
		// keep updating the destination every tick while desired
		if (bMoveToMouseCursor)
		{
			MoveToMouseCursor();
		}
	}
	else
	{
		/// inventory management actions
	}
	
}

void AdistancePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("SetDestination", IE_Pressed, this, &AdistancePlayerController::OnSetDestinationPressed);
		InputComponent->BindAction("SetDestination", IE_Released, this, &AdistancePlayerController::OnSetDestinationReleased);

		// support touch devices 
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AdistancePlayerController::MoveToTouchLocation);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AdistancePlayerController::MoveToTouchLocation);

		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ThisClass::OnLeftMouseButtonUp);

		InputComponent->BindAction("ControlTypeChange", IE_Pressed, this, &ThisClass::SwitchMouseControlMode);
	}
}

void AdistancePlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AdistanceCharacter* MyPawn = Cast<AdistanceCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AdistancePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
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

void AdistancePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AdistancePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AdistancePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AdistancePlayerController::SwitchMouseControlMode()
{
	if (MouseControlMode == EControlMode::AimControlMode)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::White, TEXT("Inventory mode"));
		MouseControlMode = EControlMode::InventoryControlMode;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::White, TEXT("Movement mode"));
		MouseControlMode = EControlMode::AimControlMode;
	}
}

void AdistancePlayerController::OnLeftMouseButtonUp()
{
	if (MouseControlMode == EControlMode::InventoryControlMode)
	{
		OnMouseButtonUp.Broadcast();
	}
	
}
