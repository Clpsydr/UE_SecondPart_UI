#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "GameStructs.h"
#include "Minimap.generated.h"

class SMinimapWidget;

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameUpdatedEvent, TArray<FVector2D>, CoordPoints);   /*, type , argument*/

UCLASS()
class DISTANCE_API UMinimap : public UWidget
{
	GENERATED_BODY()

public:

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(EditAnyWhere, Category = Appearance)
		UTexture2D* EnemyBit;

	UPROPERTY(EditAnyWhere, Category = Appearance)
		UTexture2D* MapBackground;

	UPROPERTY(EditAnyWhere, Category = Appearance)
		FMinimapData MinimapData;

	//ok just send a static array of all boxes then
	//also an array of all enemies and player? I dunno. I guess.
	
	UPROPERTY()
		FGetFloat PlayerCoordXDelegate;

	UPROPERTY(EditAnywhere, Category = Appearance)
		float PlayerCoordX = 0.5f;

	UPROPERTY()
		FGetFloat PlayerCoordYDelegate;

	UPROPERTY(EditAnywhere, Category = Appearance)
		float PlayerCoordY = 0.5f; 

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

private:

	TSharedPtr<SMinimapWidget> MapProjection;

	FMinimapData AssembleMapData() const;
	
};
