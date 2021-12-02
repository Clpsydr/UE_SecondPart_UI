#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStructs.h"
#include "Damageable.generated.h"

UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

class DISTANCE_API IDamageable
{
	GENERATED_BODY()

public:
	virtual void TakeDamage(const FDamageReport& DamageReport) = 0;
};
