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

// doesn't return 0 as non operational result, beause generic interface takes in any item
int32 UInventoryComponent::CheckSlotAvailability(int32 SlotIndex, const FEquipItem& InItem)
{
	FEquipSlot* SlotPtr = Items.Find(SlotIndex);
		
	if (SlotPtr && SlotPtr->Id == InItem.Id)
	{
		return 1;		//same object, potentially counting amount of stackable items
	}

	return -1;		// different objects or nothing
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