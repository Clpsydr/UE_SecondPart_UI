#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicProjectile.generated.h"

UCLASS()
class DISTANCE_API ABasicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicProjectile();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float Velocity = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Life")
		float Lifetime = 3.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Life")
		float Power = 5.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Effects")
		class UParticleSystemComponent* Visuals;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* HitCollider;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Stop();

	UFUNCTION()
		virtual void OnMeshHit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

private:
	FTimerHandle RemainingTTL;


};
