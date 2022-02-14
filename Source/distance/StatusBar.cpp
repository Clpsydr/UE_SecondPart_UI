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

// this is going to be unreadable by me two weeks later
// Unpacks stats components sent through array, because its all more or less floats
// in this order > hp ratio , armor ratio larm rarm lleg rleg, weapon power
// needs enough parameters to be present
void UStatusBar::UpdateCompact(TArray<float> ShortParams)
{
	if (ShortParams.Num() > 5)
	{
		if (HealthBar)
		{
			HealthBar->SetPercent(ShortParams[0]);
		}

		if (ArmorLH)
		{
			ArmorLH->SetPercent(ShortParams[1]);
		}

		if (ArmorRH)
		{
			ArmorRH->SetPercent(ShortParams[2]);
		}

		if (ArmorLL)
		{
			ArmorLL->SetPercent(ShortParams[3]);
		}

		if (ArmorRL)
		{
			ArmorRL->SetPercent(ShortParams[4]);
		}

		if (DisplayName)
		{
			FText NewText = DisplayName->GetText();
			DisplayName->SetText(NewText.FromString("Attack: " + FString::SanitizeFloat(ShortParams[5])));
		}

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