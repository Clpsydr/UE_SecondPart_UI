#include "UIManager.h"
#include "Blueprint/UserWidget.h"

AUIManager::AUIManager()
{

}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();
}

void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UUserWidget* AUIManager::ShowWidget(const EWidgetEnum EWidgetId, const int32 ZOrder)
{
	HideWidget();
	TSubclassOf<UUserWidget>* ClassPtr = WidgetClasses.Find(EWidgetId);
	if (ClassPtr && *ClassPtr)
	{
		CreateWidgetByClass(*ClassPtr, ZOrder);
	}

	return CurrentWidget;
}

void AUIManager::HideWidget()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
}

UUserWidget* AUIManager::GetCurrentWidget() const
{
	return CurrentWidget;
}

UUserWidget* AUIManager::CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder)
{
	CurrentWidget = CreateWidget(GetWorld(), WidgetClass);
	CurrentWidget->AddToViewport(ZOrder);
	return CurrentWidget;
}