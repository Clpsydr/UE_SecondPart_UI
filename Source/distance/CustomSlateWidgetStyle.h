#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "CustomSlateWidgetStyle.generated.h"

USTRUCT()
struct DISTANCE_API FCustomSlateStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FCustomSlateStyle();
	virtual ~FCustomSlateStyle();

	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle TextStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FButtonStyle ButtonStyle;

	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FCustomSlateStyle& GetDefault();
};

UCLASS(hidecategories=Object, MinimalAPI)
class UCustomSlateWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FCustomSlateStyle CustomStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &CustomStyle );
	}
};
