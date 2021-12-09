#include "LibraryWidget.h"
#include "SLibraryWidget.h"
#include "CustomSlateWidgetStyle.h"

void ULibraryWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Library.Reset();
}

TSharedRef<SWidget> ULibraryWidget::RebuildWidget()
{
	Library = SNew(SLibraryWidget)
		.Style(&CustomStyle);

	return Library.ToSharedRef();
}

/// more methods there that build widget structure interaction