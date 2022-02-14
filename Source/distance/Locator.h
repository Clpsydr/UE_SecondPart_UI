#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "Locator.generated.h"

class UInventoryComponent;

UCLASS()
class DISTANCE_API ALocator : public AEnemyPawn
{
	GENERATED_BODY()

	ALocator();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* ChestOpenArea;
	
	UPROPERTY(EditDefaultsOnly)
	UInventoryComponent* EInventory;

	bool bIsOpen = false;

	float ChestOpeningDelay = .5f;

	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
			class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnMeshOverlapEnd(UPrimitiveComponent* OverlappedComp, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex);

private:
	FTimerHandle ChestPatienceTimer;
};

