#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EquipInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEquipInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORY_API IEquipInterface
{
	GENERATED_BODY()

public:

	virtual void EquipItem(EEquipType Slot, FName ItemId) = 0;

	virtual void UnequipItem(EEquipType Slot, FName ItemId) = 0;
};
