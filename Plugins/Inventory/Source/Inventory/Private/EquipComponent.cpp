#include "EquipComponent.h"
#include "EquipInterface.h"

UEquipComponent::UEquipComponent()
{
	EquipSlots.Add(0, EEquipType::Es_Head);
	EquipSlots.Add(1, EEquipType::Es_Back);
	EquipSlots.Add(2, EEquipType::Es_Body);
	EquipSlots.Add(3, EEquipType::Es_Belt);
	EquipSlots.Add(4, EEquipType::Es_Weapon);
	EquipSlots.Add(5, EEquipType::Es_Buff);
}

// returns availability code by trying to shove InItem into SlotIndex of current inventory
int32 UEquipComponent::CheckSlotAvailability(int32 SlotIndex, const FEquipItem& InItem)
{
	EEquipType* EquipSlotPtr = EquipSlots.Find(SlotIndex);

	if (InItem.Type == EItemType::It_Equip && EquipSlotPtr && *EquipSlotPtr == InItem.EquipType)
	{
		return -1;		// swappable, considers equip as different by default
	}

	return 0; //wrong type
}

void UEquipComponent::SetItem(int32 SlotIndex, const FEquipSlot& Item)
{
	auto* InventoryOwner = GetOwner();

	// Valid check for any sort of interface
	if (!InventoryOwner->GetClass()->ImplementsInterface(UEquipInterface::StaticClass()))
	{
		Super::SetItem(SlotIndex, Item);
		return;
	}

	// Cast works only if interface is pure c++, use ::Execute for BP interfaces
	IEquipInterface* EquipInterface = Cast<IEquipInterface>(InventoryOwner);
	if (EquipInterface)
	{
		EEquipType EquipSlot = EquipSlots.FindChecked(SlotIndex);

		if (auto* ItemInfo = GetItem(SlotIndex))
		{
			if (GetWorld()->GetTimerManager().IsTimerActive(BuffExpirationTimer))
			{
				GetWorld()->GetTimerManager().ClearTimer(BuffExpirationTimer);
			}

			ClearItem(SlotIndex);
		}

		Super::SetItem(SlotIndex, Item);
		EquipInterface->EquipItem(EquipSlot, Item.Id);

		// temporary equipment functionality 
		if (EquipSlot == EEquipType::Es_Buff)
		{
			BuffTimerParameters.BindUFunction(this, FName("ClearItem"), SlotIndex);
			GetWorld()->GetTimerManager().SetTimer(BuffExpirationTimer, BuffTimerParameters, BuffDuration, false);
		}
	}
}
	
void UEquipComponent::ClearItem(int32 SlotIndex)
{
	auto* InventoryOwner = GetOwner();

	if (!InventoryOwner->GetClass()->ImplementsInterface(UEquipInterface::StaticClass()))
	{
		Super::ClearItem(SlotIndex);
		return;
	}

	IEquipInterface* EquipInterface = Cast<IEquipInterface>(InventoryOwner);
	if (EquipInterface)
	{
		EEquipType EquipSlot = EquipSlots.FindChecked(SlotIndex);

		if (auto* ItemInfo = GetItem(SlotIndex))
		{
			EquipInterface->UnequipItem(EquipSlot, ItemInfo->Id);
		}

		Super::ClearItem(SlotIndex);
	}
}
