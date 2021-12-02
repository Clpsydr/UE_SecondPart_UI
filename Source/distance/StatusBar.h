#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusBar.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class DISTANCE_API UStatusBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HealthBar;

	// TODO: as an alternative, bind a container with them , and find children on construction
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		TArray<UProgressBar*> ArmorSet;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* DisplayName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* AmmoCount;


public:
	virtual void NativeConstruct() override;

	virtual void UpdateHP(float NewFraction);

	virtual void UpdateName(FString NewName) ;

private:
	
};
