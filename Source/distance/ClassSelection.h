#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipLibrary.h"
#include "ClassSelection.generated.h"

class UButton;
class UDataTable;

UCLASS()
class DISTANCE_API UClassSelection : public UUserWidget
{
	GENERATED_BODY()

private:
	TArray<FEquipItem> ItemNames;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ClassSelectFirst;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* ClassSelectSecond;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* ClassSelectThird;

	UFUNCTION()
		void OnMainClassSelected();

	UFUNCTION()
		void OnSecondClassSelected();

	UFUNCTION()
		void OnThirdClassSelected();

	UFUNCTION()
		void AddingStarterItems(TArray<FEquipSlot>& ItemSet);
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintType, EditAnywhere)
		UDataTable* EquipInfoTable;
};
