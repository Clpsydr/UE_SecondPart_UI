#include "InventoryComponent.h"

void UInventoryComponent::SetItem(int32 SlotIndex, const FEquipSlot& Item)
{
	ClearItem(SlotIndex);
	if (Item.Count > 0)
	{
		Items.Add(SlotIndex, Item);
	}
}

void UInventoryComponent::ClearItem(int32 SlotIndex)
{
	Items.Remove(SlotIndex);
}

// comparing whether InItem can fit in Slot of SlotIndex
// returns 0 if slot is occupied by another object
// -1 if free
int32 UInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FEquipItem& InItem)
{
	FEquipSlot* SlotPtr = Items.Find(SlotIndex);
	if (SlotPtr && SlotPtr->Id != InItem.Id)   // should be (SlotPtr == nullptr && SlotPtr->Id == InItem.Id) but it crashes
	{
		return 0;
	}
	return -1;
}

void UInventoryComponent::UseItem(int32 SlotIndex)
{
	if (Items.Find(SlotIndex)->Count > 1)
	{
		Items.Find(SlotIndex)->Count--;
	}
	else
	{
		ClearItem(SlotIndex);
	}
}

void UInventoryComponent::ClearAll()
{
	Items.Empty();
}

void UInventoryComponent::ReportItems()
{
	GLog->Log(ELogVerbosity::Warning, *FString::Printf(TEXT("Total items now: ")));  
	for (auto& Item : Items)
	{
		GLog->Log(ELogVerbosity::Warning, *FString::Printf(TEXT("Item on index %d, %s, of %d amount"), Item.Key, *(Item.Value.Id).ToString(), Item.Value.Count));  
	}
}