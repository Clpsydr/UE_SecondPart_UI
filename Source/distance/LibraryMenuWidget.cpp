#include "LibraryMenuWidget.h"

#include "distanceCoreStyle.h"
#include "LibraryWidget.h"
#include "SLibraryWidget.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/Image.h"
#include "Components/NativeWidgetHost.h"  

void ULibraryMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (LibWidget)
	{
		//now it just doesnt exist instead of crashing, I guess thats better.
		LibWidget->CustomStyle = FdistanceCoreStyle::Get().GetWidgetStyle<FCustomSlateStyle>("WS_DefaultStyle");
	}

	if (CloseButton)
	{
		CloseButton->SetBackgroundColor(FdistanceCoreStyle::Get().GetColor("Red"));
	}

	if (BGImage)
	{
		BGImage->SetBrush(*FdistanceCoreStyle::Get().GetBrush("BGImg"));
		Cast<UButtonSlot>(BGImage->Slot)->SetPadding(FdistanceCoreStyle::Get().GetMargin("DefaultPadding"));
	}
}

void ULibraryMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}