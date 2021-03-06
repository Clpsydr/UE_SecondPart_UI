#include "InventoryManagerComponent.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "EquipComponent.h"
#include "InventoryCellWidget.h"

#define MAXCRATEDISPLAY 5

UInventoryManagerComponent::UInventoryManagerComponent()
{
}

void UInventoryManagerComponent::Init(UInventoryComponent* InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;

	if (LocalInventoryComponent && ItemData && InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->ParentInventory = InInventoryComponent;

		InventoryWidget->Init(FMath::Max(MinInvSize, LocalInventoryComponent->GetItemsNum()));			// setting up minimal inventory display to fit all possible items.
		InventoryWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);
		InventoryWidget->OnItemUse.AddUObject(this, &ThisClass::OnItemUseFunc);			// applies option to use items from inventory.
		
		for (const auto& Item : LocalInventoryComponent->GetAllItems())
		{
			auto* CurrentItem = GetItemData(Item.Value.Id);
			if (CurrentItem)
			{
				InventoryWidget->AddItem(Item.Value, *CurrentItem, Item.Key);
			}
		}
	}
}

void UInventoryManagerComponent::InitChest(UInventoryComponent* InInventoryComponent)
{
	if (InInventoryComponent && ChestContentsWidgetClass)
	{
		ChestInventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), ChestContentsWidgetClass);
		ChestInventoryWidget->AddToViewport();
		ChestInventoryWidget->ParentInventory = InInventoryComponent;

		ChestInventoryWidget->Init(FMath::Max(MAXCRATEDISPLAY, InInventoryComponent->GetItemsNum()));
		ChestInventoryWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);

		for (const auto& Item : InInventoryComponent->GetAllItems())
		{
			auto* CurrentItem = GetItemData(Item.Value.Id);
			if (CurrentItem)
			{
				ChestInventoryWidget->AddItem(Item.Value, *CurrentItem, Item.Key);
			}
		}
	}
}

void UInventoryManagerComponent::InitInventory(UInventoryComponent* InInventoryComponent, UInventoryWidget* InWidget, TSubclassOf<UInventoryWidget> InWidgetClass)
{
	if (InInventoryComponent && ItemData && InWidgetClass)
	{
		InWidget = CreateWidget<UInventoryWidget>(GetWorld(), InWidgetClass);
		InWidget->AddToViewport();
		InWidget->ParentInventory = InInventoryComponent;

		InWidget->Init(FMath::Max(MAXCRATEDISPLAY, InInventoryComponent->GetItemsNum()));
		InWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);

		for (const auto& Item : InInventoryComponent->GetAllItems())
		{
			auto* CurrentItem = GetItemData(Item.Value.Id);
			if (CurrentItem)
			{
				InWidget->AddItem(Item.Value, *CurrentItem, Item.Key);
			}
		}
	}
}

void UInventoryManagerComponent::InitEquip(UInventoryComponent* InInventoryComponent)
{
	LocalEquipComponent = InInventoryComponent;

	if (InInventoryComponent && EquipWidgetClass)
	{
		EquipWidget = CreateWidget<UInventoryWidget>(GetWorld(), EquipWidgetClass);
		EquipWidget->AddToViewport();
		EquipWidget->ParentInventory = InInventoryComponent;

		EquipWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);

		for (const auto& Item : InInventoryComponent->GetAllItems())
		{
			auto* CurrentItem = GetItemData(Item.Value.Id);
			if (CurrentItem)
			{		
				EquipWidget->AddItem(Item.Value, *CurrentItem, Item.Key);
			}
		}
	}
}

// clears inventory and reinitializes widget
void UInventoryManagerComponent::Refresh(UInventoryComponent* InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;

	if (LocalInventoryComponent && ItemData && InventoryWidgetClass)
	{
		LocalInventoryComponent->ClearAll();
	}
}

void UInventoryManagerComponent::ShowWidgets(UInventoryComponent* InInventoryComponent, UInventoryComponent* InEquipComponent)
{
	if (!InventoryWidget && !EquipWidget)
	{
		Init(InInventoryComponent);
		InitEquip(InEquipComponent);
	}
}

void UInventoryManagerComponent::ShowChest(UInventoryComponent* InInvComponent)
{
	ChestInventoryComponent = InInvComponent;
	if (ChestInventoryWidget) 
	{
		ChestInventoryWidget->RemoveFromParent();
		ChestInventoryWidget = nullptr;
	}

	InitChest(InInvComponent);
}

void UInventoryManagerComponent::HideWidgets()
{
	if (InventoryWidget )
	{
		InventoryWidget->RemoveFromParent();
		InventoryWidget = nullptr;
	}

	if (EquipWidget)
	{
		EquipWidget->RemoveFromParent();
		EquipWidget = nullptr;
	}
}

void UInventoryManagerComponent::HideChest()
{
	if (ChestInventoryWidget)
	{
		ChestInventoryWidget->RemoveFromParent();
		ChestInventoryWidget = nullptr;
	}
}

const FEquipItem* UInventoryManagerComponent::GetItemData(const FName& Id) const 
{
	return ItemData ? ItemData->FindRow<FEquipItem>(Id, "") : nullptr;
}

// Gives new set of items, which are hardcoded in the ClassSelection widget
// TODO: actually check which items exist at which indexes instead of blindly wiping it before item addition
void UInventoryManagerComponent::SupplyItemSet(const TArray<FEquipSlot>& NewItems, UInventoryComponent* InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;
	
	if (LocalInventoryComponent && ItemData && InventoryWidgetClass) 
	{
		int32 i = 0;
		for (const auto& Item : NewItems)
		{
			auto* ItemRecord = GetItemData(Item.Id);

			if (ItemRecord)
			{
				GLog->Log(ELogVerbosity::Warning, *FString::Printf(TEXT("Trying to issue %s, of %d amount"), *ItemRecord->Name, Item.Count));  
				LocalInventoryComponent->SetItem(i, Item);
				i++;
			}
		}

		if (InventoryWidget)
		{
			InventoryWidget->RemoveFromParent();
		}
		Init(InInventoryComponent);

		LocalInventoryComponent->ReportItems();  //debug stuff
	}
}

void UInventoryManagerComponent::OnItemUseFunc(UInventoryCellWidget* UsedCell)
{
	//ideally you just apply onitemdropfunc with UsedCell and ___ equipcell that has Usable slot marking
	if (UsedCell == nullptr)
	{
		return;
	}

	auto* ThisInventory = UsedCell->GetParentInventory();
	const FEquipSlot* LiveItemSlot = ThisInventory->GetItem(UsedCell->IndexInInventory);

	// trying to equip the buff item
	LocalEquipComponent->SetItem(Cast<UEquipComponent>(LocalEquipComponent)->GetBuffSlotIndex(), UsedCell->GetItemFromSlot());
	
	//there is no equipment widget update, because buff effects are fed directly on character
	
	// update widget accordingly  
	if (LiveItemSlot && LiveItemSlot->Count > 1)
	{
		UsedCell->SetAmount(FString::FromInt(LiveItemSlot->Count - 1)); 
	}
	else
	{
		UsedCell->Clear();
	}

	// reduce item count
	ThisInventory->UseItem(UsedCell->IndexInInventory);
	LocalInventoryComponent->ReportItems();
}

void UInventoryManagerComponent::OnItemDropFunc(UInventoryCellWidget* FromCell, UInventoryCellWidget* ToCell)
{
	///
	
	if (FromCell == nullptr || ToCell == nullptr)
	{
		return;
	}

	auto* FromInventory = FromCell->GetParentInventory();
	auto* ToInventory = ToCell->GetParentInventory();

	if (FromInventory == nullptr || ToInventory == nullptr)
	{
		return;
	}

	const FEquipSlot DraggedItem = FromCell->GetItemFromSlot();
	if (DraggedItem.Count == 0)
	{
		return;
	}
	const FEquipSlot OverlappedItem = ToCell->GetItemFromSlot();
	
	/// 

	const FEquipItem* FromInfo = GetItemData(DraggedItem.Id);

	// cant equip or drag into inaccessible inventory
	if (ToInventory->CheckSlotAvailability(ToCell->IndexInInventory, *FromInfo) == 0)
	{
		return;
	}
	
	// have to swap with something not fitting to equipment in use
	if (GetItemData(OverlappedItem.Id) && FromInventory->CheckSlotAvailability(FromCell->IndexInInventory, *GetItemData(OverlappedItem.Id)) == 0)
	{
		GLog->Log(ELogVerbosity::Error, *FString::Printf(TEXT("Item under cursor is %s"), *GetItemData(OverlappedItem.Id)->Name));
		return;
	}

	FromCell->Clear();

	FEquipSlot ReturnedItem = OverlappedItem;
	FEquipSlot DroppedItem = DraggedItem;

	const FEquipItem* ReturnedItemInfo = ReturnedItem.Count > 0 ? GetItemData(ReturnedItem.Id) : nullptr;
	const FEquipItem* DroppedItemInfo = GetItemData(DroppedItem.Id);

	if (ReturnedItemInfo)
	{
		// if swapping occurs, verifying possibility to put item in original slow (in case of equipment inventory)
		FromCell->AddItemToSlot(ReturnedItem, *ReturnedItemInfo);
		FromInventory->SetItem(FromCell->IndexInInventory, ReturnedItem);
	}
	else
	{
		FromInventory->ClearItem(FromCell->IndexInInventory);
	}

	ToCell->Clear();
	ToCell->AddItemToSlot(DroppedItem, *DroppedItemInfo);
	ToInventory->SetItem(ToCell->IndexInInventory, DroppedItem); 

	// TODO: Stackable items in swapping part

	/*FEquipSlot ReturnedItem = OverlappedItem;							// duplicates of slots to avoid losing data
	FEquipSlot DroppedItem = DraggedItem;

	if (OverlappedItemAmount > 0)	// possible item stacking
	{
		DroppedItem.Count = FMath::Max(OverlappedItemAmount, DraggedItem.Count);
		if (DraggedItem.Count <= DroppedItem.Count)		// counting the amount of stacked items
		{
			ReturnedItem.Id = DroppedItem.Id;		
			ReturnedItem.Count = DraggedItem.Count - DroppedItem.Count;
		}
	}
	
	//returned item is null there in case somthing got stacked completely, but ...
	const FEquipItem* ReturnedItemInfo = ReturnedItem.Count > 0 ? GetItemData(ReturnedItem.Id) : nullptr;
	const FEquipItem* DroppedItemInfo = GetItemData(DroppedItem.Id);

	FromCell->Clear();
	//...but since we are checking for it, there should be a clear case for swapping
	// this so far only works for "else" case?!
	if (ReturnedItemInfo)		// is there anything to return to the original slot?
	{
		FromCell->AddItemToSlot(ReturnedItem, *ReturnedItemInfo);
		FromInventory->SetItem(FromCell->IndexInInventory, ReturnedItem);   
	}
	else
	{
		FromInventory->ClearItem(FromCell->IndexInInventory);
	}

	ToCell->Clear();
	ToCell->AddItemToSlot(DroppedItem, *DroppedItemInfo);

	ToInventory->SetItem(ToCell->IndexInInventory, DroppedItem);*/
	
	FromInventory->ReportItems();
	ToInventory->ReportItems();
}