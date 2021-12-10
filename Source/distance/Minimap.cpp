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

	//???? Collect actors? Collect geometry? construct level geometry in the controlled way?
	// ??????????????? How to convert object coordinates to box2d
	// ????????????? level manager with geodata > simple uwidget that takes data and represents it as text
	// Plug data widget to minimap, assemble information from that.
	//FBox2D NewBox = GetWorld()
	//NewData.GeometryPoints.Add();

	//NewData.EnemyPoints;
	//NewData.GeometryPoints;
	
	return NewData;
}
