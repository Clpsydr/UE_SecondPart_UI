#include "SMinimapWidget.h"
#include "Math/UnrealMathUtility.h"
#include "SlateOptMacros.h"
#include "SlateBasics.h"
#include "GameStructs.h"
#include "SlateExtras.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMinimapWidget::Construct(const FArguments& InArgs)
{
	MapInfoInput = InArgs._MapInfoInput;
	EnemyBit = InArgs._EnemyBit;
	MapBackground = InArgs._MapBackground;

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SBorder)
			[
				CreateDrawing()
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<SWidget> SMinimapWidget::CreateDrawing()
{
	return SNew(SImage);
}

int32 SMinimapWidget::OnPaint(const FPaintArgs& Args,
	const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements,
	int32 LayerId,
	const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	const bool bEnabled = true;
	const FVector2D LocalCoords = AllottedGeometry.GetLocalSize();
	const FMinimapData MapInfo = MapInfoInput.Get();

	FSlateBrush MapBG;
	if (MapBackground)
	{
		MapBG.SetResourceObject(MapBackground);

		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			&MapBG,
			bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect,
			FColor::White
		);

		++LayerId;
	}

	if (MapInfo.GeometryPoints.Num() > 0 || MapInfo.EnemyPoints.Num() > 0 || MapInfo.PlayerPoints.Num() > 0)
	{
		TArray<FVector2D> PlotPoints;

		// Its increidbly irritating that I can't do a single little thing outside of this solution's frame.
		// Hardly any structure that you need works, can't pass any dynamic property without jumping through flaming hoops.
		// So it ends up being a copypaste of a solution that isn't even covering all points in the task. I feel like I don't really learn anything.
		for (auto& i : MapInfo.GeometryPoints)
		{
			PlotPoints.Add(LocalCoords * i.Min);
			PlotPoints.Add(LocalCoords * i.Max);

			FSlateDrawElement::MakeLines(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(),
				PlotPoints,
				bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect,
				FColor::Blue,
				true,
				AllottedGeometry.Scale
				);

				PlotPoints.Empty();
		}

		for (int i = 0; i < MapInfo.PlayerPoints.Num(); i++)
		{ 
			FVector2D PlayerPosition = MapInfo.PlayerPoints[i] * LocalCoords;

			FSlateBrush PlayerSprite;
			if (EnemyBit)
			{
				PlayerSprite.SetResourceObject(EnemyBit);

				FSlateDrawElement::MakeBox(
					OutDrawElements,
					LayerId,
					AllottedGeometry.ToPaintGeometry(PlayerPosition - PlayerSprite.ImageSize * 0.5f, PlayerSprite.ImageSize),
					&PlayerSprite,
					bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect,
					FColor::White
				);

				++LayerId;
			}
			
			


		/*	const FVector2D SplineStart(PlayerPosition);  //* FVector2D(1.f, 0.95f)
			const FVector2D SplineStartDir(FVector2D(0.5f, 0.5f));  //pposx * 1.1 , 0
			const FVector2D SplineEnd(PlayerPosition );  //* FVector2D(1.f, 1.05f)
			const FVector2D SplineEndDir(FVector2D(0.5f, 0.5f)); //pposx * 1.1 , 0

			FSlateDrawElement::MakeCubicBezierSpline(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(),
				SplineStart, SplineStartDir,
				SplineEnd, SplineEndDir,
				AllottedGeometry.Scale,
				bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect,
				FColor::Red
			);*/

			//

			FText PlayerName;
			PlayerName.FromString(FString::FromInt(i));

			FSlateFontInfo FontInfo = FCoreStyle::GetDefaultFontStyle("Regular", 5);
			FontInfo.OutlineSettings.OutlineColor = FLinearColor::Yellow;
			FontInfo.OutlineSettings.OutlineSize = 2;

			FSlateDrawElement::MakeText(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(),
				PlayerName,
				FontInfo,
				bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect,
				FColor::White);
		}

		for (int i = 0; i < MapInfo.EnemyPoints.Num(); i++)
		{
			FVector2D EnemyPosition = MapInfo.EnemyPoints[i] * LocalCoords;
			TArray<FVector2D> EnemyGeom;   
			EnemyGeom.Add(EnemyPosition + FVector2D(-10.f, -10.f));
			EnemyGeom.Add(EnemyPosition + FVector2D(10.f, -10.f));
			EnemyGeom.Add(EnemyPosition + FVector2D(10.f, 10.f));
			EnemyGeom.Add(EnemyPosition + FVector2D(-10.f, 10.f));
			EnemyGeom.Add(EnemyPosition + FVector2D(-10.f, -10.f));

			FSlateDrawElement::MakeLines(
				OutDrawElements,
				LayerId,
				AllottedGeometry.ToPaintGeometry(),
				EnemyGeom,
				bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect,
				FColor::Red,
				true,
				AllottedGeometry.Scale
			);
		}

	}
	else
	{
		FSlateFontInfo FontInfo = FCoreStyle::GetDefaultFontStyle("Regular", 15);
		FontInfo.OutlineSettings.OutlineColor = FLinearColor::Blue;
		FontInfo.OutlineSettings.OutlineSize = 2;

		FSlateDrawElement::MakeText(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			TEXT("- No world information was received -"),
			FontInfo,
			bEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect,
			FColor::Red);
	}
	
	return LayerId;
}
	
bool SMinimapWidget::bIsMapInfo(const FMinimapData MapInfo) 
{
	return (MapInfo.GeometryPoints.Num() > 0 || MapInfo.EnemyPoints.Num() > 0 || MapInfo.PlayerPoints.Num() > 0);
}
