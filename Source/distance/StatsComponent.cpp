#include "StatsComponent.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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

void UStatsComponent::ModifyHealth(float HPValue)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HPValue, 0.f, MaxHealth);
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

