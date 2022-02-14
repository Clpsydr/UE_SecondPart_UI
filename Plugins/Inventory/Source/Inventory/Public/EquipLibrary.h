#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/DataTable.h"
#include "EquipLibrary.generated.h"

UENUM()
enum class EItemType : uint8
{
	It_Equip,
	It_Resource,
	It_Quest,
	It_Ammo,
	It_None,
	It_Usable,
};

UENUM()
enum class EItemRarity : uint8
{
	Ir_Normal,
	Ir_Rare,
	Ir_Special,
};

UENUM()
enum class EEquipType : uint8
{
	Es_None,
	Es_Head,
	Es_Back,
	Es_Body,
	Es_Belt,
	Es_Weapon,
	Es_Buff,
};

USTRUCT(BlueprintType)
struct FArmorIntegrity
{
	GENERATED_BODY()

		UPROPERTY()
		float LHand;

	UPROPERTY()
		float RHand;

	UPROPERTY()
		float LLeg;

	UPROPERTY()
		float RLeg;

	FORCEINLINE FArmorIntegrity& operator+=(const float rhs)
	{
		this->LHand += rhs;
		this->RHand += rhs;
		this->LLeg += rhs;
		this->RLeg += rhs;

		return *this;
	}

	FORCEINLINE FArmorIntegrity& operator-=(const float rhs)
	{
		this->LHand -= rhs;
		this->RHand -= rhs;
		this->LLeg -= rhs;
		this->RLeg -= rhs;

		return *this;
	}
};

class UInventoryCellWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemUse, UInventoryCellWidget* /*target cell*/)

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventoryCellWidget* /*From*/, UInventoryCellWidget* /*To*/)

USTRUCT(BlueprintType)
struct FEquipItem : public FTableRowBase  
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "General")
		FName Id;

	UPROPERTY(EditDefaultsOnly, Category = "General")
		FString Name;		// shoulve been FText???

	UPROPERTY(EditDefaultsOnly, Category = "General")
		FString Description;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		EItemType Type;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		EEquipType EquipType;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		EItemRarity Rarity;

	UPROPERTY(EditDefaultsOnly, Category = "Assets")
		TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Assets")
		TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		int32 Level;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		bool bStackable;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float ArmorBonus;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float HealthBonus;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float HPregen;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float AttackBonus;
};

USTRUCT(BlueprintType)
struct FEquipSlot //: public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName Id = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 Count;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EItemType Type = EItemType::It_None;
};