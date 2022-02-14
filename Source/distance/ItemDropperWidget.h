#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "distance/GameStructs.h"
#include "ItemDropperWidget.generated.h"

class UImage;
class UTextBlock;
class UBorder;

UCLASS()
class DISTANCE_API UItemDropperWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UBorder* WidgetFrame;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> SpawnClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> ToolTipType;

	UPROPERTY()
		AActor* SpawnedActor = nullptr;

	UPROPERTY()
		APlayerController* PlayerController;

	UPROPERTY(BlueprintType)
		FEnemyData DataForWidget;

	void OnMouseButtonUp();

	UFUNCTION(BlueprintCallable, Category = "Get results")
	FEnemyData GetToolTipParams();

	UPROPERTY(EditAnywhere)
		FString DragItemName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* DragItemIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* DragItemDescription;

	
};
