#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleMenuWidget.generated.h"

class UButton;
class UCheckBox;
class USlider;
class UComboBoxString;
class UWidgetSwitcher;

UCLASS()
class DISTANCE_API UTitleMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level loading params")
		FName LoadLevelName;

	// Root Section
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
		UButton* NewGameButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* ReturnButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* OptionsButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		UButton* QuitGameButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWidgetSwitcher* MenuSwitcher;

	// Option Section
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* GraphicOptionButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* SoundOptionButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* ControlOptionButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* BackToRootMenuButton;
	//

	//	Graphic Section
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		USlider* GraphicSettingSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UComboBoxString* ShadowsSettingCombo;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UCheckBox* IsVsyncEnabledBullet;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* ResetSettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* BackFromGraphicsButton;
	//

	// Sound Section
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		USlider* MasterVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		USlider* MusicVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		USlider* SoundVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* BackFromSoundButton;
	//

	// Controls Section
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		USlider* MouseSensitivitySlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* KeybindsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* BackFromControlsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UCheckBox* InvertMouseBullet;
	//

	UFUNCTION()   //necessary for binding dynamic delegates
		void OnNewGameClicked();

	UFUNCTION()
		void OnQuitGameClicked();

	UFUNCTION()
		void OnReturnClicked();

	UFUNCTION()
		void OnOptionsClicked();

	UFUNCTION()
		void OnGraphicSectionClicked();

	UFUNCTION()
		void OnSoundSectionClicked();

	UFUNCTION()
		void OnControlsSectionClicked();

	UFUNCTION()
		void OnReturnToRootClicked();

	UFUNCTION()
		void OnReturnToOptionsClicked();

	UFUNCTION()
		void OnGraphicQualityChanged(float NewValue);

	UFUNCTION()
		void OnShadowSettingChanged();

	UFUNCTION()
		void OnVsyncSettingChanged(bool NewValue);

	UFUNCTION()
		void OnVideoSettingsReset();

	UFUNCTION()
		void OnMasterVolumeChanged(float NewValue);

	UFUNCTION()
		void OnMusicVolumeChanged(float NewValue);

	UFUNCTION()
		void OnSoundVolumeChanged(float NewValue);

	UFUNCTION()
		void OnMouseSensitivityChanged(float NewValue);

	UFUNCTION()
		void OnKeybindsClicked();

	UFUNCTION()
		void OnMouseInvertChanged(bool NewValue);

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetAnimOptional), Transient)
		UWidgetAnimation* NewGameAnimation;

public:
	virtual void NativeConstruct() override;

private:
	
};
