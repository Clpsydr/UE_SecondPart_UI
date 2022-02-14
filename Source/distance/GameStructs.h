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

USTRUCT(BlueprintType)
struct FEnemyData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		FString Name;

	UPROPERTY(BlueprintReadOnly)
		FString Description;

	UPROPERTY(BlueprintReadOnly)
		UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly)
		float Health;

	UPROPERTY(BlueprintReadOnly)
		float Range;
};

