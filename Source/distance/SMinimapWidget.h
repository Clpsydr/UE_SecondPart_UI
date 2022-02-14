#pragma once
#include "CoreMinimal.h"
#include "GameStructs.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FOnGameUpdated, TArray<FVector2D> /*set of points*/)

class DISTANCE_API SMinimapWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMinimapWidget)
		: _EnemyBit(),
		_MapBackground()
	{
	}

	SLATE_ARGUMENT(UTexture2D*, EnemyBit)

	SLATE_ARGUMENT(UTexture2D*, MapBackground)

	SLATE_ATTRIBUTE(FMinimapData, MapInfoInput)			// Incoming drawing data

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FOnGameUpdated OnGameUpdated;

	int32 OnPaint(const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled) const;

protected:
	TSharedRef<SWidget> CreateDrawing();

	UTexture2D* EnemyBit = nullptr;

	UTexture2D* MapBackground = nullptr;

	TAttribute<FMinimapData> MapInfoInput;

	//void OnImageUpdated();

	bool bIsMapInfo(const FMinimapData MapInfo);			//		Verifying if theres anything to draw
};
