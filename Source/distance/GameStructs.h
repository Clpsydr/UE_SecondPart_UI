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

USTRUCT(BlueprintType)
struct FDrawnGeometry
{
	GENERATED_BODY()

		UPROPERTY()
		TArray <FVector2D> GeometryPoints;

	UPROPERTY()
		FString GeomName;
};

USTRUCT(BlueprintType)
struct FMinimapData
{
	GENERATED_BODY()

		UPROPERTY()
			TArray<FBox2D> GeometryPoints;

		UPROPERTY()
			TMap<int32, FVector2D> PlayerPoints;

		UPROPERTY()
			TMap<int32, FVector2D> EnemyPoints;

		UPROPERTY()
			FDrawnGeometry DrawObjectSet;
};

