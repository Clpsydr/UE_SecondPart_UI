#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "Locator.generated.h"

UCLASS()
class DISTANCE_API ALocator : public AEnemyPawn
{
	GENERATED_BODY()

//public:
	// got to add inventory there later on
//	AEnemyPawn();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
};

