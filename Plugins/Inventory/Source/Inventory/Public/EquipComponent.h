#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "EquipLibrary.h"
#include "EquipComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORY_API UEquipComponent : public UInventoryComponent
{
	GENERATED_BODY()
	
public:
	
	UEquipComponent();

	UPROPERTY(EditAnywhere)
		TMap<int32, EEquipType> EquipSlots;

	virtual int32 CheckSlotAvailability(int32 SlotIndex, const FEquipItem& InItem) override;

	virtual void SetItem(int32 SlotIndex, const FEquipSlot& Item) override;

	UFUNCTION()
	virtual void ClearItem(int32 SlotIndex) override;

	int32 GetBuffSlotIndex() { return 5; };

protected:

	float BuffDuration = 5.f;

private:

	FTimerDelegate BuffTimerParameters;

	FTimerHandle BuffExpirationTimer;

};
