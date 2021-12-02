// Fill out your copyright notice in the Description page of Project Settings.
#include "StatusBar.h"
#include "Components/TextBlock.h"
#include "Containers/UnrealString.h"
#include "Components/ProgressBar.h"

void UStatusBar::NativeConstruct()
{
	Super::NativeConstruct();

}

void UStatusBar::UpdateHP(float NewFraction)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(NewFraction);
	}
}

void UStatusBar::UpdateName(FString NewName)
{
	if (DisplayName)
	{
		FText NewText = DisplayName->GetText();
		DisplayName->SetText(NewText.FromString(NewName));
	}
}