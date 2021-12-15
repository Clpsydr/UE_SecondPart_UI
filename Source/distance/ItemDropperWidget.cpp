#include "ItemDropperWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/BoxComponent.h"
#include "distancePlayerController.h"
#include "EnemyPawn.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

void UItemDropperWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UItemDropperWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (auto* CurrentController = Cast<AdistancePlayerController>(PlayerController))
	{
		CurrentController->OnMouseButtonUp.AddUObject(this, &ThisClass::OnMouseButtonUp);
	}

	AEnemyPawn* DefaultActor = Cast<AEnemyPawn>(SpawnClass->GetDefaultObject());
	DataForWidget = DefaultActor->GetStats();
	DataForWidget.Icon = DefaultActor->MapIcon;

	if (DragItemDescription)
	{
		DragItemDescription->SetText(FText::FromString(DataForWidget.Name));
	}

	if (DragItemIcon)
	{
		DragItemIcon->Brush.SetResourceObject(DefaultActor->MapIcon);
	}
}

void UItemDropperWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SpawnedActor && PlayerController)
	{
		FVector WorldMousePosition;
		FVector WorldMouseDirection;

		PlayerController->DeprojectMousePositionToWorld(WorldMousePosition, WorldMouseDirection);

		// avoiding recursive spawning and such
		// better probably to make a separate collision channel for allowed spawning zones
		FCollisionQueryParams HitParams;
		HitParams.AddIgnoredActor(SpawnedActor);
		HitParams.AddIgnoredActor(PlayerController->GetPawn());
		FHitResult OutHit;
		constexpr float Range = 50000.f;
		GetWorld()->LineTraceSingleByChannel(OutHit, WorldMousePosition, WorldMousePosition +
								Range * WorldMouseDirection, ECollisionChannel::ECC_WorldStatic, HitParams);

		if (OutHit.bBlockingHit)
		{
			SpawnedActor->SetActorLocation(OutHit.Location + FVector(0.f, 0.f, 0.f)); //Bounds.Z / 2
		}
	}
}

FReply UItemDropperWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnClass);
	}

	return FReply::Handled();
}

void UItemDropperWidget::OnMouseButtonUp()
{
			// newcenter only on spawning
			// newcenter only at all without bounds.
	if (SpawnedActor)
	{
		FVector OldCenter;
		FVector Bounds;
		SpawnedActor->GetActorBounds(false, OldCenter, Bounds, true);

		FVector NewCenter = SpawnedActor->GetActorLocation();
		NewCenter.Z = 175.f;						//175.f + OldCenter.Z/Bounds.Z  sinks them at center level somehow
		SpawnedActor->SetActorLocation(NewCenter);
		SpawnedActor = nullptr;
	}
}

FEnemyData UItemDropperWidget::GetToolTipParams()
{
	return DataForWidget;
}
