#include "InventoryItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/MenuAnchor.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInventoryItem::NativePreConstruct()
{
	SetColorAndOpacity(TintedColor);
	if (ItemDescription)
	{
		ItemDescription->SetText(FText::FromString(ItemName));
	}
}

FReply UInventoryItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;  //could be just DetectDrag
	}

	return FReply::Handled();
}

void UInventoryItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDragDropAction::StaticClass());
	UItemDragDropAction* ItemOperation = Cast<UItemDragDropAction>(OutOperation);

	if (ItemOperation)
	{
		ItemOperation->DefaultDragVisual = this;  //supplies information on dragged object 
		//ItemOperation->DefaultDragVisual = CreateWidget()
		//supplying CreateWidget, which will be set to hidden lets overriding the display
		//ItemOperation->Payload = /// actual content that is being transported there in this case

		SetRenderOpacity(.5f);
		ItemDescription->SetText(FText::FromString(ItemName));
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		ItemOperation->OnDragCancelled.AddDynamic(this, &ThisClass::DropCancelRestore);
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

//unfinished function
//The idea for solution was that I'd put every item in menuanchor, which would remain in the widget even when we remove all items.
// then compare InGeometry of current widget to each anchor in the 
//something like  FMath::Abs(InGeometry.AbsolutePosition.Y - anchor[i]->GetCachedGeometry().AbsolutePosition.Y)  
//						< anchor[i].GetAbsoluteSize.Y / 2
// is that even a sane way to do that.

bool UInventoryItem::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UMenuAnchor* ThisAnchor = Cast<UMenuAnchor>(GetParent());
	UVerticalBox* VerticalBox = Cast<UVerticalBox>(ThisAnchor->GetParent());
	UItemDragDropAction* ItemAction = Cast<UItemDragDropAction>(InOperation);
	UWidget* DraggedWidget = ItemAction->DefaultDragVisual;

	if (VerticalBox && ItemAction && DraggedWidget && this != DraggedWidget)
	{
		const int32 IndexToAnchors = VerticalBox->GetChildIndex(DraggedWidget->GetParent());         

		if (IndexToAnchors >= 0)
		{
			UMenuAnchor* DraggedMenu = Cast<UMenuAnchor>(VerticalBox->GetChildAt(IndexToAnchors));   //remembering current menu from anchors
			DraggedMenu->RemoveChildAt(0);

			const TArray<UWidget*> AllAnchors = VerticalBox->GetAllChildren();
			TArray<UWidget*> RestChildren;
			for (int32 i = 0; i < AllAnchors.Num(); i++)							//clearing other anchors
			{
				RestChildren.Add(Cast<UMenuAnchor>(AllAnchors[i])->GetChildAt(0));
				Cast<UMenuAnchor>(AllAnchors[i])->ClearChildren();
			}

			for (int32 i = 0; i < AllAnchors.Num(); i++)
			{
				//VerticalBox->AddChildToVerticalBox(RestChildren[i])->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);

				if (AllAnchors[i] == DraggedMenu)
				{
					Cast<UMenuAnchor>(AllAnchors[i])->AddChild(DraggedWidget);
					//VerticalBox->AddChildToVerticalBox(ItemAction->DefaultDragVisual)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
					SetColorAndOpacity(TintedColor);
				}
				else
				{
					Cast<UMenuAnchor>(AllAnchors[i])->AddChild(RestChildren[i]);
				}
			}

			return true;
		}
	}

	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
}

bool UInventoryItem::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation && InOperation->DefaultDragVisual)
	{
		DropCancelRestore(InOperation);
		return true;
	}
	
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryItem::DropCancelRestore(UDragDropOperation* Operation)
{
	UInventoryItem* Item = Cast<UInventoryItem>(Operation->DefaultDragVisual);
	if (Item)
	{
		ItemDescription->SetText(FText::FromString(ItemName));
		SetRenderOpacity(1.f);
		SetVisibility(ESlateVisibility::Visible);
	}
}
