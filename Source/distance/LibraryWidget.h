#pragma once

#include "CoreMinimal.h"
#include "SLibraryWidget.h"
#include "Components/Widget.h"
#include "LibraryWidget.generated.h"


UCLASS()
class DISTANCE_API ULibraryWidget : public UWidget
{
	GENERATED_BODY()

public:

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(EditAnywhere, Category = Appearance, Meta = (DisplayName = Style))
		FCustomSlateStyle CustomStyle;

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	
private:
	TSharedPtr<SLibraryWidget> Library;
};
