#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UIManager.generated.h"

class UUserWidget;

UENUM(BlueprintType)
enum class EWidgetEnum : uint8
{
	Wid_None,
	Wid_GameplayHUD,
	Wid_Inventory,
	Wid_PauseMenu,
	Wid_Library,
	Wid_GameOver,
	Wid_DebugSelection,
};

UCLASS()
class DISTANCE_API AUIManager : public AHUD
{
	GENERATED_BODY()

public:
	AUIManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UUserWidget* ShowWidget(const EWidgetEnum EWidgetId, const int32 ZOrder = 0);

	UFUNCTION(BlueprintCallable)
	void HideWidget();

	UFUNCTION(BlueprintPure)
		UUserWidget* GetCurrentWidget() const;

protected:
	UFUNCTION()
		UUserWidget* CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder = 0);

	UPROPERTY(EditAnywhere)
		TMap<EWidgetEnum, TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY()
		UUserWidget* CurrentWidget;

};