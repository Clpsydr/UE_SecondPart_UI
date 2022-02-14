#include "StatsComponent.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxArmor.LHand = 10;
	MaxArmor.RHand = 10;
	MaxArmor.LLeg = 10;
	MaxArmor.RLeg = 10;
}

void UStatsComponent::TakeDamage(const FDamageReport& DmgReport)
{
	float DamageValue = DmgReport.DamageValue;
	ModifyHealth(DamageValue);

	if (CurrentHealth == 0.f)
	{
		if (OnDie.IsBound())
		{
			OnDie.Broadcast();
		}
	}
	else
	{
		if (OnHealthChanged.IsBound())
		{
			OnHealthChanged.Broadcast(DamageValue);
		}
	}
}

float UStatsComponent::GetHealth(bool bIsRatio)
{
	return bIsRatio ? CurrentHealth / MaxHealth : CurrentHealth;
}

// sending compact values in an ordered list, to be extracted in the same order
const TArray<float> UStatsComponent::GetShortenedParams()
{
	return {CurrentHealth/MaxHealth, 
		CurrentArmor.LHand / MaxArmor.LHand, 
		CurrentArmor.RHand / MaxArmor.RHand, 
		CurrentArmor.LLeg/ MaxArmor.LLeg,
		CurrentArmor.RLeg / MaxArmor.RLeg,
		Attack
	};
}

void UStatsComponent::ModifyHealth(float HPValue)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HPValue, 0.f, MaxHealth);
}

void UStatsComponent::ArmorUpdate()
{
	CurrentArmor.LHand = FMath::Clamp(CurrentArmor.LHand + ArmorRegen, CurrentArmor.LHand + ArmorRegen, MaxArmor.LHand);
	CurrentArmor.RHand = FMath::Clamp(CurrentArmor.RHand + ArmorRegen, CurrentArmor.RHand + ArmorRegen, MaxArmor.RHand);
	CurrentArmor.LLeg = FMath::Clamp(CurrentArmor.LLeg + ArmorRegen, CurrentArmor.LLeg + ArmorRegen, MaxArmor.LLeg);
	CurrentArmor.RLeg = FMath::Clamp(CurrentArmor.RLeg + ArmorRegen, CurrentArmor.RLeg+ ArmorRegen, MaxArmor.RLeg);
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UStatsComponent::ApplyStatBonus(const FEquipItem* Item)
{
	MaxArmor += Item->ArmorBonus;
	MaxHealth += Item->HealthBonus;
	Attack += Item->AttackBonus;
	HPRegen += Item->HPregen;
}

void UStatsComponent::RemoveStatBonus(const FEquipItem* Item)
{
	MaxArmor -= Item->ArmorBonus;
	CurrentArmor.LHand = FMath::Clamp(CurrentArmor.LHand, CurrentArmor.LHand, MaxArmor.LHand);
	CurrentArmor.RHand = FMath::Clamp(CurrentArmor.RHand, CurrentArmor.RHand, MaxArmor.RHand);
	CurrentArmor.LLeg = FMath::Clamp(CurrentArmor.LLeg, CurrentArmor.LLeg, MaxArmor.LLeg);
	CurrentArmor.RLeg = FMath::Clamp(CurrentArmor.RLeg, CurrentArmor.RLeg, MaxArmor.RLeg);

	MaxHealth -= Item->HealthBonus;
	CurrentHealth = FMath::Clamp(CurrentHealth, CurrentHealth, MaxHealth);

	Attack -= Item->AttackBonus;
	HPRegen -= Item->HPregen;
}
