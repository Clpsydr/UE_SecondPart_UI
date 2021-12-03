// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Damageable.h"
#include "GameStructs.h"
#include "StatsComponent.h"
#include "distanceCharacter.generated.h"

class UWidgetComponent;

UCLASS(Blueprintable)
class AdistanceCharacter : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	AdistanceCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void TakeDamage(const FDamageReport& DamageReport) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Temp elements")
		float HealthPoints = 50;

	UFUNCTION(BlueprintCallable, Category = "Events")
		void Death();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UStatsComponent* PlayerStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UWidgetComponent* PlayerStatusWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<class UUserWidget> StatusWidgetClass;

	bool IsAlive();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	void Harm(float Points);

	UFUNCTION(BlueprintCallable, Category = "Methods")
	void UpdateWidgets();
};

