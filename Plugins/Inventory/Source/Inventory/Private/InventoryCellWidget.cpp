#include "InventoryCellWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryWidget.h"
#include "InventoryComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

bool UInventoryCellWidget::AddItemToSlot(const FEquipSlot& ItemSlot, const FEquipItem& ItemInfo)
{
	if (ItemSlot.Count == 0)
	{
		Clear();
		Item.Count = 0;
		return true;
	}

/*	if (bHasItem)		// occupied slot doesnt assume a new item?
	{
		return false;
	}*/

	if (ItemIcon)		// load image if present or set placeholder
	{
		ItemIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemIcon->SetBrushFromTexture(ItemInfo.Icon.LoadSynchronous());
	}
	else
	{
		ItemIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemIcon->SetBrushFromTexture(NoImageSubstitute);
	}

	if (Amount && (ItemSlot.Count > 1))			// load quantity if present
	{
		Amount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Amount->SetText(FText::FromString(FString::FromInt(ItemSlot.Count)));
	}
	else
	{
		Amount->SetVisibility(ESlateVisibility::Collapsed);
	}

	Item = ItemSlot;
	return true;
}

void UInventoryCellWidget::Clear()
{
	if (Item.Count == 0)
	{
		return;
	}

	if (ItemIcon)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (Amount)
	{
		Amount->SetVisibility(ESlateVisibility::Collapsed);
	}

	Item.Count = 0;
}

FReply UInventoryCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// Consumable activation process
	if (Item.Count > 0 && Item.Type == EItemType::It_Usable && InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		GLog->Log(ELogVerbosity::Warning, *FString::Printf(TEXT("Pressed right mouse button on item with %d amount"), Item.Count));

		//broadcasting back to inventory manager to use the item
		OnItemUse.Broadcast(this);
	}
	
	// Dragndrop start process
	if (bCanDrag && Item.Count > 0 && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	return FReply::Handled();
}

void UInventoryCellWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	if (OutOperation)
	{
		OutOperation->DefaultDragVisual = this;
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

bool UInventoryCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation && InOperation->DefaultDragVisual && InOperation->DefaultDragVisual != this)
	{
		auto* FromCell = Cast<UInventoryCellWidget>(InOperation->DefaultDragVisual);
		if (FromCell)
		{
				OnItemDrop.Broadcast(FromCell, this);
				return true;
		}
	}

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryCellWidget::ChangeVisibility(bool bIsVisible)
{
	if (Item.Count > 0)
	{
		if (bIsVisible)
		{
			ItemIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			if (Item.Count > 1)
			{
				Amount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
		}
		else
		{
			ItemIcon->SetVisibility(ESlateVisibility::Collapsed);
			Amount->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UInventoryCellWidget::SetParent(UInventoryWidget* ParentWidget)
{
	ParentInvWidget = ParentWidget;
}

UInventoryComponent* UInventoryCellWidget::GetParentInventory() const
{
	return ParentInvWidget ? ParentInvWidget->ParentInventory : nullptr;
}

void UInventoryCellWidget::SetAmount(FString NewValue)
{
	Amount->SetText(FText::FromString(NewValue)); 
}
