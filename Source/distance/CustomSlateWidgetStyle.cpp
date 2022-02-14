#include "CustomSlateWidgetStyle.h"
#include "distanceCoreStyle.h"

FCustomSlateStyle::FCustomSlateStyle()
{
	// DEFAULT STYLE SETTING, and other visual stuff in ISlateStyle
	TextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("EmbossedText");
	ButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("NoBorder.Normal");

	// applying this on construct would work ahead of the slate library initialization anyway

	/*const FCustomSlateStyle DefaultStyle = FdistanceCoreStyle::Get().GetWidgetStyle<FCustomSlateStyle>("WS_DefaultStyle");
	TextStyle = DefaultStyle.TextStyle;
	ButtonStyle = DefaultStyle.ButtonStyle;*/
}

FCustomSlateStyle::~FCustomSlateStyle()
{
}

const FName FCustomSlateStyle::TypeName(TEXT("FCustomSlateStyle"));

const FCustomSlateStyle& FCustomSlateStyle::GetDefault()
{
	static FCustomSlateStyle Default;
	return Default;
}

void FCustomSlateStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
	FSlateWidgetStyle::GetResources(OutBrushes);   // good thing to call a parental method just in case
	//OtherStyle.GetResources(OutBrushes);  // will be needed in case of widget crashing, since I cant tell which widget requires resource pulling
}

