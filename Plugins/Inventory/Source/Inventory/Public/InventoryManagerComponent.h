#pragma once

#include "CoreMinimal.h"
#include "EquipLibrary.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"

class UInventoryComponent;
class UEquipComponent;
class UInventoryWidget;
class UInventoryCellWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryManagerComponent();

	void Init(UInventoryComponent* InInventoryComponent);

	void InitInventory(UInventoryComponent* InInventoryComponent, UInventoryWidget* InWidget, TSubclassOf<UInventoryWidget> InWidgetClass);

	void InitEquip(UInventoryComponent* InInventoryComponent);

	void InitChest(UInventoryComponent* InInventoryComponent);

	const FEquipItem* GetItemData(const FName& Id) const;

	void SupplyItemSet(const TArray<FEquipSlot>& NewItems, UInventoryComponent* InInventoryComponent);

	void Refresh(UInventoryComponent* InInventoryComponent);

	UFUNCTION(BlueprintCallable, Category = "Show visuals")
		void ShowWidgets(UInventoryComponent* InInventoryComponent, UInventoryComponent* InEquipComponent);

	UFUNCTION(BlueprintCallable, Category = "Show visuals")
		void HideWidgets();

	UFUNCTION(BlueprintCallable, Category = "Show visuals")
		void ShowChest(UInventoryComponent* InInvComponent);

	UFUNCTION(BlueprintCallable, Category = "Show visuals")
		void HideChest();	

protected:

	UPROPERTY(EditAnywhere)
		UDataTable* ItemData;

	UPROPERTY(EditAnywhere)
		int32 MinInvSize = 30;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
		UInventoryComponent* LocalInventoryComponent;

	UPROPERTY()
		UInventoryComponent* LocalEquipComponent;

	UPROPERTY()
		UInventoryComponent* ChestInventoryComponent;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UInventoryWidget> EquipWidgetClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UInventoryWidget> ChestContentsWidgetClass;

	UPROPERTY()
		UInventoryWidget* EquipWidget;

	UPROPERTY()
		UInventoryWidget* InventoryWidget;

	UPROPERTY()
		UInventoryWidget* ChestInventoryWidget;

	void OnItemDropFunc(UInventoryCellWidget* FromCell, UInventoryCellWidget* ToCell);

	void OnItemUseFunc(UInventoryCellWidget* UsedCell);

};
