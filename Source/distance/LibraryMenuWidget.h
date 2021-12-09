#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LibraryMenuWidget.generated.h"

class ULibraryWidget;
class UTextBlock;
class UButton;
class UImage;

/**
 * 
 */
UCLASS()
class DISTANCE_API ULibraryMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		ULibraryWidget* LibWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* CloseButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Transient)
		UImage* BGImage;


};
