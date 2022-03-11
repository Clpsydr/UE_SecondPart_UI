#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipLibrary.h"
#include "InventoryCellWidget.generated.h"

class UImage;
class UTextBlock;
class UInventoryWidget;
class UInventoryCellWidget;
class UInventoryComponent;

UCLASS()
class INVENTORY_API UInventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:

		UPROPERTY(BlueprintReadOnly, Meta = (Bindwidget))
			UImage* ItemIcon;

		UPROPERTY(BlueprintReadOnly, Meta = (Bindwidget))
			UTextBlock* Amount;

		UPROPERTY()
			FEquipSlot Item;

		UPROPERTY()
			UInventoryWidget* ParentInvWidget;

	public:
		bool AddItemToSlot(const FEquipSlot& ItemSlot, const FEquipItem& ItemInfo);

		void ChangeVisibility(bool bIsVisible);

		void Clear();

		const FEquipSlot& GetItemFromSlot() { return Item; }

		UPROPERTY(EditAnywhere)
			int32 IndexInInventory = INDEX_NONE;		

		FOnItemDrop OnItemDrop;

		FOnItemUse OnItemUse;

		void SetAmount(FString NewValue);

		void SetParent(UInventoryWidget* ParentWidget);

		UInventoryComponent* GetParentInventory() const;


protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UFUNCTION()
		void OnDragCancelledHandle(UDragDropOperation* Operation);

	UPROPERTY(EditAnywhere)
		bool bCanDrag = true;

private:

	UPROPERTY(BlueprintType, EditAnywhere)
		UTexture2D* NoImageSubstitute;

};
