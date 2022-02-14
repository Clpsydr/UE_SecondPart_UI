#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventoryCellWidget.h"
#include "Components/Button.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (auto* Cell : Cells)
	{
		InitCell(Cell);
	}

	if (FilterEquip)
	{
		FilterEquip->OnPressed.AddDynamic(this, &ThisClass::OnPressFilterEquip);
	}

	if (FilterConsumables)
	{
		FilterConsumables->OnPressed.AddDynamic(this, &ThisClass::OnPressFilterAmmo);
	}

	if (ClearFilter)
	{
		ClearFilter->OnPressed.AddDynamic(this, &ThisClass::OnPressFilterClear);
	}
}

void UInventoryWidget::Init(int32 ItemsCount)
{
	if (GridWidget)
	{
		GridWidget->ClearChildren();

		for (int32 i = 0; i < ItemsCount; i++)
		{
			if (auto* Cell = CreateCell())
			{
				Cell->IndexInInventory = i;
				GridWidget->AddChildToUniformGrid(Cell, i / RowWidth, i % RowWidth);
			}
		}
	}
}

void UInventoryWidget::DeleteItem(int32 SlotIndex)
{
	if (GridWidget)
	{
		UInventoryCellWidget* Found = nullptr;
		UInventoryCellWidget** FoundPtr = Cells.FindByPredicate([SlotIndex](UInventoryCellWidget* Cell)
		{
			return Cell && Cell->IndexInInventory == SlotIndex;
		});

		if (FoundPtr)
		{
			Found = *FoundPtr;
		}

		if (Found)
		{
			Found->Clear();
		}
	}
};

bool UInventoryWidget::AddItem(const FEquipSlot& ItemSlot, const FEquipItem& ItemInfo, int32 SlotIndex)
{
	if (ItemInfo.Type == EItemType::It_Resource)
	{
		if (ResourceCell)
		{
			return ResourceCell->AddItemToSlot(ItemSlot, ItemInfo);
		}
	}

	if (GridWidget)
	{
		UInventoryCellWidget* Found = nullptr;
		UInventoryCellWidget** FoundPtr = Cells.FindByPredicate([SlotIndex](UInventoryCellWidget* Cell)
		{
			return Cell && Cell->IndexInInventory == SlotIndex;
		});

		if (FoundPtr)
		{
			Found = *FoundPtr;
		}
		else
		{
			for (auto* Cell : Cells)
			{
				if (Cell->GetItemFromSlot().Count == 0)
				{
					Found = Cell;
					break;
				}
			}
		}

		if (Found)
		{
			return Found->AddItemToSlot(ItemSlot, ItemInfo);
		}
	}

	return false;
}

void UInventoryWidget::OnPressFilterEquip()
{
	RefreshCells(EItemType::It_Equip);
}

void UInventoryWidget::OnPressFilterAmmo()
{
	RefreshCells(EItemType::It_Ammo);
}

void UInventoryWidget::OnPressFilterClear()
{
	RefreshCells(EItemType::It_None);
}

UInventoryCellWidget* UInventoryWidget::CreateCell()
{
	if (CellWidgetClass)
	{
		auto* Cell = CreateWidget<UInventoryCellWidget>(this, CellWidgetClass);
		Cells.Add(Cell);

		InitCell(Cell);
	
		return Cell;
	}

	return nullptr;
}

void UInventoryWidget::InitCell(UInventoryCellWidget* NewCell)
{
	if (NewCell)
	{
		NewCell->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);
		NewCell->OnItemUse.AddUObject(this, &ThisClass::OnItemUseFunc);
		NewCell->SetParent(this);
	}
}

void UInventoryWidget::OnItemDropFunc(UInventoryCellWidget* FromCell, UInventoryCellWidget* ToCell)
{
	OnItemDrop.Broadcast(FromCell, ToCell);
}

void UInventoryWidget::OnItemUseFunc(UInventoryCellWidget* ThisCell)
{
	OnItemUse.Broadcast(ThisCell);
}

// lazy refresh that just hides existing items. Should probably reinit entire widget from manager
// but that would require letting widget know manager to reinit the whole widget with new filter
void UInventoryWidget::RefreshCells(EItemType ByFilter)
{
	if (GridWidget)
	{
		for (auto* ThisCell : Cells)
		{
			if (ThisCell->GetItemFromSlot().Count > 0)
			{
				if (ByFilter == EItemType::It_None || ByFilter == ThisCell->GetItemFromSlot().Type)
				{
					ThisCell->ChangeVisibility(true);
				}
				else
				{
					ThisCell->ChangeVisibility(false);
				}
			}
		}
	}
}

