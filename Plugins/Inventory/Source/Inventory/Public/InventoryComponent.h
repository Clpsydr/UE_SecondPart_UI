#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipLibrary.h"
#include "InventoryComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
	TMap<int32, FEquipSlot> Items;

public:

	const FEquipSlot* GetItem(int32 SlotIndex) const { return Items.Find(SlotIndex); };

	virtual void SetItem(int32 SlotIndex, const FEquipSlot& Item);

	virtual void ClearItem(int32 SlotIndex);

	virtual void UseItem(int32 SlotIndex);

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FEquipItem& InItem);

	const TMap<int32, FEquipSlot>& GetAllItems() const { return Items; }

	int32 GetItemsNum() const { return Items.Num(); }

	void ClearAll();

	void ReportItems();


};