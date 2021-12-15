#pragma once

#include "CoreMinimal.h"
#include "ItemDragDropAction.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "RenderResource.h"
#include "InventoryItem.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class DISTANCE_API UInventoryItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FString ItemName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* ItemIcon; 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* ItemDescription;

	UPROPERTY(BlueprintType, EditAnywhere)
		FLinearColor TintedColor;

	virtual void NativePreConstruct();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UFUNCTION()
		void DropCancelRestore(UDragDropOperation* Operation);
	
};
