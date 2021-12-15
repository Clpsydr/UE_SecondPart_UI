#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasicProjectile.h"
#include "GameStructs.h"
#include "EnemyPawn.generated.h"

class UTexture2D;
class UWidgetComponent;

UCLASS()
class DISTANCE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* ProjectileSource;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* HitCollider;
	
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
		TSubclassOf<class ABasicProjectile> ProjectileType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
		float ReloadTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
		float FireRange = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UWidgetComponent* StatusWidget;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<class UUserWidget> StatusWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		bool bIsAggressive;

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void TurnTo();
	
	virtual void Fire();

	virtual FEnemyData GetStats();

	void Reload();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UTexture2D* MapIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UStatsComponent* EnemyStats;
	
private:
	UPROPERTY()
	APawn* PlayerPawn;

	bool bIsReadyToFire;

	float CurrentHealth;

	void UpdateWidgets();

	FTimerHandle ReloadTimerHandle;

	bool InRange(FVector OriginLoc, FVector TargetLoc, float Range);
};
