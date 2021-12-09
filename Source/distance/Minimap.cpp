#include "Minimap.h"
#include "SMinimapWidget.h"

void UMinimap::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	
	MapProjection.Reset();
}

TSharedRef<SWidget> UMinimap::RebuildWidget()
{
	MapProjection = SNew(SMinimapWidget)				// passing over information
		.MapInfoInput_UObject(this, &ThisClass::AssembleMapData)
		.MapBackground(MapBackground)
		.EnemyBit(EnemyBit);
	
	return MapProjection.ToSharedRef();
}

FMinimapData UMinimap::AssembleMapData() const
{
	FMinimapData NewData;
	
	NewData.PlayerPoints.Add(0.f, 
		FVector2D 
		(PlayerCoordXDelegate.IsBound() ? PlayerCoordXDelegate.Execute() : PlayerCoordX,
			PlayerCoordYDelegate.IsBound() ? PlayerCoordYDelegate.Execute() : PlayerCoordY
		));

	//NewData.EnemyPoints;
	//NewData.GeometryPoints;
	
	return NewData;
}
