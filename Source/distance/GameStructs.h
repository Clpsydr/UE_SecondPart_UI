#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "GameStructs.generated.h"

USTRUCT(BlueprintType)
struct FDamageReport
{
	GENERATED_BODY()

		UPROPERTY()
		float DamageValue;

	UPROPERTY()
		class AActor* Instigator;

	UPROPERTY()
		class AActor* DamageCause;
};

USTRUCT(BlueprintType)
struct FArmorIntegrity
{
	GENERATED_BODY()

		UPROPERTY()
			float LHand;

		UPROPERTY()
			float RHand;

		UPROPERTY()
			float LLeg;

		UPROPERTY()
			float RLEg;
};
