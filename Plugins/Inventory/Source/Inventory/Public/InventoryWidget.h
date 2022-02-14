#pragma once

#include "CoreMinimal.h"
#include "EquipLibrary.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;
class UInventoryCellWidget;
class UInventoryComponent;
class UButton;

UCLASS()
class INVENTORY_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void Init(int32 ItemsCount);

	void DeleteItem(const int32 SlotIndex);

	bool AddItem(const FEquipSlot& ItemSlot, const FEquipItem& ItemInfo, int32 SlotIndex);

	FOnItemDrop OnItemDrop;

	FOnItemUse OnItemUse;

	UFUNCTION()
	void RefreshCells(EItemType ByFilter);

	UPROPERTY()
		UInventoryComponent* ParentInventory;

protected:

	UPROPERTY(EditDefaultsOnly)
		int32 RowWidth= 5;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetOptional))
		UUniformGridPanel* GridWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UInventoryCellWidget> CellWidgetClass;

	UPROPERTY(EditDefaultsOnly, Meta = (BindWidgetOptional))
	UInventoryCellWidget* ResourceCell;

	UPROPERTY(EditDefaultsOnly, Meta = (BindWidgetOptional))
		UButton* FilterEquip;

	UPROPERTY(EditDefaultsOnly, Meta = (BindWidgetOptional))
		UButton* FilterConsumables;

	UPROPERTY(EditDefaultsOnly, Meta = (BindWidgetOptional))
		UButton* ClearFilter;
	
	UPROPERTY(BlueprintReadWrite)
		TArray<UInventoryCellWidget*> Cells;

	UFUNCTION()
		void OnPressFilterEquip();

	UFUNCTION()
		void OnPressFilterAmmo();

	UFUNCTION()
		void OnPressFilterClear();

	UInventoryCellWidget* CreateCell();

	void InitCell(UInventoryCellWidget* NewCell);

	void OnItemDropFunc(UInventoryCellWidget* FromCell, UInventoryCellWidget* ToCell);

	void OnItemUseFunc(UInventoryCellWidget* ThisCell);

};
