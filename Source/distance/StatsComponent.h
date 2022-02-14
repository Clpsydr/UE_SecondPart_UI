#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "EquipLibrary.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, DamageValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DISTANCE_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatsComponent();

	///
	UPROPERTY(BlueprintAssignable)
		FOnDie OnDie;

	UPROPERTY(BlueprintAssignable)
		FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Stat component")
		void TakeDamage(const FDamageReport& DmgReport);
	///
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game parameters")
		float MaxHealth = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game parameters")
		float HPRegen = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game parameters")
		float ArmorRegen = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game parameters")
		FArmorIntegrity MaxArmor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game parameters")
		float Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game parameters")
		FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game parameters")
		FString Description;

	UFUNCTION(BlueprintCallable, Category = "Stat component")
		float GetHealth(bool bIsRatio);

	UFUNCTION(BlueprintCallable, Category = "Stat component")
		const TArray<float> GetShortenedParams();

	UFUNCTION(BlueprintCallable, Category = "Stat component")
		void ModifyHealth(float HPValue);

	UFUNCTION(BlueprintCallable, Category = "Stat component")
		void ArmorUpdate();

	void ApplyStatBonus(const FEquipItem* Item);

	void RemoveStatBonus(const FEquipItem* Item);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		float CurrentHealth;

	UPROPERTY()
		FArmorIntegrity CurrentArmor;

	
};
