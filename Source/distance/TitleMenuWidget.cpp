// Fill out your copyright notice in the Description page of Project Settings.
#include "TitleMenuWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

void UTitleMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameButton)
	{
		NewGameButton->OnPressed.AddDynamic(this, &ThisClass::OnNewGameClicked);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnPressed.AddDynamic(this, &ThisClass::OnQuitGameClicked);
	}

	if (ReturnButton)
	{
		ReturnButton->OnPressed.AddDynamic(this, &ThisClass::OnReturnClicked);
	}

	if (OptionsButton)
	{
		OptionsButton->OnPressed.AddDynamic(this, &ThisClass::OnOptionsClicked);
	}

	//
	if (GraphicOptionButton)
	{
		OptionsButton->OnPressed.AddDynamic(this, &ThisClass::OnGraphicSectionClicked);
	}

	if (SoundOptionButton)
	{
		OptionsButton->OnPressed.AddDynamic(this, &ThisClass::OnSoundSectionClicked);
	}

	if (ControlOptionButton)
	{
		OptionsButton->OnPressed.AddDynamic(this, &ThisClass::OnControlsSectionClicked);
	}

	if (BackToRootMenuButton)
	{
		OptionsButton->OnPressed.AddDynamic(this, &ThisClass::OnReturnToRootClicked);
	}
	//

	//
	if (GraphicSettingSlider)
	{
		GraphicSettingSlider->OnValueChanged.AddDynamic(this, &ThisClass::OnGraphicQualityChanged);
	}

	// Ive got lost in ways to correctly write it on first try
	/*if (ShadowsSettingCombo)
	{
		ShadowsSettingCombo->On.AddDynamic(this, &ThisClass::OnShadowSettingChanged);
	}*/

	if (IsVsyncEnabledBullet)
	{
		IsVsyncEnabledBullet->OnCheckStateChanged.AddDynamic(this, &ThisClass::OnVsyncSettingChanged);
	}

	if (ResetSettingsButton)
	{
		ResetSettingsButton->OnPressed.AddDynamic(this, &ThisClass::OnVideoSettingsReset);
	}

	if (BackFromGraphicsButton)
	{
		BackFromGraphicsButton->OnPressed.AddDynamic(this, &ThisClass::OnReturnToOptionsClicked);
	}
	//

	//
	if (MasterVolumeSlider)
	{
		MasterVolumeSlider->OnValueChanged.AddDynamic(this, &ThisClass::OnMasterVolumeChanged);
	}

	if (SoundVolumeSlider)
	{
		SoundVolumeSlider->OnValueChanged.AddDynamic(this, &ThisClass::OnSoundVolumeChanged);
	}

	if (MusicVolumeSlider)
	{
		MusicVolumeSlider->OnValueChanged.AddDynamic(this, &ThisClass::OnMusicVolumeChanged);
	}

	if (BackFromSoundButton)
	{
		BackFromSoundButton->OnPressed.AddDynamic(this, &ThisClass::OnReturnToOptionsClicked);
	}
	//

	//
	if (MouseSensitivitySlider)
	{
		MouseSensitivitySlider->OnValueChanged.AddDynamic(this, &ThisClass::OnMouseSensitivityChanged);
	}

	if (KeybindsButton)
	{
		KeybindsButton->OnPressed.AddDynamic(this, &ThisClass::OnKeybindsClicked);
	}

	if (InvertMouseBullet)
	{
		InvertMouseBullet->OnCheckStateChanged.AddDynamic(this, &ThisClass::OnMouseInvertChanged);
	}

	if (BackFromControlsButton)
	{
		BackFromControlsButton->OnPressed.AddDynamic(this, &ThisClass::OnReturnToOptionsClicked);
	}
}

void UTitleMenuWidget::OnNewGameClicked()
{
	if (LoadLevelName.IsValid())
	{
		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	}
}

void UTitleMenuWidget::OnQuitGameClicked()
{
	GEngine->Exec(GetWorld(), TEXT("exit"));
}

void UTitleMenuWidget::OnReturnClicked()
{
	if (GetWorld()->IsPaused())
	{
		GetWorld()->GetFirstPlayerController()->SetPause(false);
	}
	RemoveFromParent();
}

void UTitleMenuWidget::OnOptionsClicked()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Blue, TEXT("Clicked on options!"));
	MenuSwitcher->SetActiveWidgetIndex(1);			// This is really bad (hidden implied order of menus) but im running out of time
}

void UTitleMenuWidget::OnGraphicSectionClicked()
{
	MenuSwitcher->SetActiveWidgetIndex(2);
}

void UTitleMenuWidget::OnSoundSectionClicked()
{
	MenuSwitcher->SetActiveWidgetIndex(3);
}

void UTitleMenuWidget::OnControlsSectionClicked()
{
	MenuSwitcher->SetActiveWidgetIndex(4);
}

void UTitleMenuWidget::OnReturnToRootClicked()
{
	MenuSwitcher->SetActiveWidgetIndex(0);
}

void UTitleMenuWidget::OnReturnToOptionsClicked()
{
	MenuSwitcher->SetActiveWidgetIndex(1);
}

void UTitleMenuWidget::OnMasterVolumeChanged(float NewValue)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Blue, TEXT("Master volume changed to " + FString::SanitizeFloat(NewValue)));
}

void UTitleMenuWidget::OnMusicVolumeChanged(float NewValue)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Blue, TEXT("Music volume changed to " + FString::SanitizeFloat(NewValue)));
}

void UTitleMenuWidget::OnSoundVolumeChanged(float NewValue)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Blue, TEXT("Sound volume changed to " + FString::SanitizeFloat(NewValue)));
}

void UTitleMenuWidget::OnMouseSensitivityChanged(float NewValue)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Blue, TEXT("Mouse sensitivity changed to " + FString::SanitizeFloat(NewValue)));
}

void UTitleMenuWidget::OnKeybindsClicked()
{
	//report on keybind button pressed
}

void UTitleMenuWidget::OnMouseInvertChanged(bool NewValue)
{
	//report on changed mouse invertion
}

void UTitleMenuWidget::OnGraphicQualityChanged(float NewValue)
{
	//report on current graphic quality
}

void UTitleMenuWidget::OnShadowSettingChanged()
{
	//report on current combobox shadow status
}

void UTitleMenuWidget::OnVsyncSettingChanged(bool NewValue)
{
	//report on vsync
}

void UTitleMenuWidget::OnVideoSettingsReset()
{
	//report on video settings status
}
