#include "ClassSelection.h"
#include "Components/Button.h"
#include "Engine/DataTable.h"
#include "distanceCharacter.h"

void UClassSelection::NativeConstruct()
{
	Super::NativeConstruct();

	if (ClassSelectFirst)
	{
		ClassSelectFirst->OnPressed.AddDynamic(this, &ThisClass::OnMainClassSelected);
	}

	if (ClassSelectSecond)
	{
		ClassSelectSecond->OnPressed.AddDynamic(this, &ThisClass::OnSecondClassSelected);
	}

	if (ClassSelectThird)
	{
		ClassSelectThird->OnPressed.AddDynamic(this, &ThisClass::OnThirdClassSelected);
	}
}

void UClassSelection::OnMainClassSelected()
{
	TArray<FEquipSlot> FreeStuff;
	FreeStuff.Add({ "helmet", 1, EItemType::It_Equip});
	FreeStuff.Add({ "batteries", 5, EItemType::It_Usable});
	FreeStuff.Add({ "keyCard", 1, EItemType::It_Quest});
	AddingStarterItems(FreeStuff);
}

void UClassSelection::OnSecondClassSelected()
{
	TArray<FEquipSlot> FreeStuff;
	FreeStuff.Add({ "sword", 1, EItemType::It_Equip });
	FreeStuff.Add({ "beacon", 2, EItemType::It_Usable });
	FreeStuff.Add({ "grenades", 3, EItemType::It_Equip });
	FreeStuff.Add({ "keyCard", 2, EItemType::It_Quest });
	AddingStarterItems(FreeStuff);
}

void UClassSelection::OnThirdClassSelected()
{
	TArray<FEquipSlot> FreeStuff;
	FreeStuff.Add({ "booster", 1, EItemType::It_Equip });
	FreeStuff.Add({ "gun", 1, EItemType::It_Equip });
	FreeStuff.Add({ "batteries", 2, EItemType::It_Usable });
	FreeStuff.Add({ "datapad", 1, EItemType::It_Quest });
	FreeStuff.Add({ "keyCard", 3, EItemType::It_Quest });
	AddingStarterItems(FreeStuff);
}

void UClassSelection::AddingStarterItems(TArray<FEquipSlot>& ItemSet)
{
	if (EquipInfoTable)
	{
		TArray<FName> BigNames = EquipInfoTable->GetRowNames();
		for (FName somename : BigNames)
		{
			FString NewString = somename.GetPlainNameString();
			GLog->Log(ELogVerbosity::Display, *FString::Printf(TEXT("found a %s"), *NewString));
		}

		APawn* CurrentPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (CurrentPlayer)
		{
			Cast<AdistanceCharacter>(CurrentPlayer)->GenerateItems(ItemSet);
		}
	}
}

