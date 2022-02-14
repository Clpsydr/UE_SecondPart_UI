#pragma once

#include "CoreMinimal.h"
#include "CustomSlateWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

class DISTANCE_API SLibraryWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLibraryWidget)
	{}

	// possible slate events for a button and populating the list
	SLATE_STYLE_ARGUMENT(FCustomSlateStyle, Style);

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	const FButtonStyle* ButtonStyle = nullptr;

	const FTextBlockStyle* TextStyle = nullptr;

};

