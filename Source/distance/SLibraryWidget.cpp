// Fill out your copyright notice in the Description page of Project Settings.
#include "SLibraryWidget.h"
#include "SlateOptMacros.h"
#include "SlateBasics.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLibraryWidget::Construct(const FArguments& InArgs)
{
	ButtonStyle = &InArgs._Style->ButtonStyle;  // this specifically has to be passed by reference, for the sake of it being changed as an attribute
	TextStyle = &InArgs._Style->TextStyle;
	
	ChildSlot
	[
		SNew(SGridPanel)
		.FillColumn(0, 0.3f)
		.FillColumn(1, 0.7f)
		.FillRow(0, 0.1f)
		.FillRow(1, 0.8f)
		.FillRow(2, 0.1f)

		+SGridPanel::Slot(0, 0)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBorder)
			.Padding(FMargin(15))
			[
				SNew(STextBlock)
				.TextStyle(TextStyle)
				.Text(FText::FromString("Library"))
			]
		]

		+SGridPanel::Slot(0, 1)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()		
			[
				SNew(STextBlock)
				.TextStyle(TextStyle)
				.Text(FText::FromString("Topics"))
			]
			+SVerticalBox::Slot()
			[
				SNew(SBorder)
				.Padding(FMargin(15))
				[
					SNew(SScrollBox)
				]
			]
		]

		+SGridPanel::Slot(1, 1)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SNew(SBorder)
				.Padding(FMargin(15))
				[
					SNew(SScrollBox)
					+SScrollBox::Slot()
					[
						SNew(STextBlock)
						.TextStyle(TextStyle)
						.Text(FText::FromString("Description window"))
					]
				]
			]
		]

		+SGridPanel::Slot(0, 2)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SButton)
			.ButtonStyle(ButtonStyle)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Close"))
				.TextStyle(TextStyle)
			]
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
