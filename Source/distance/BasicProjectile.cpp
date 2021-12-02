#include "BasicProjectile.h"
#include "distanceCharacter.h"
#include "Components/BoxComponent.h"
#include "GameStructs.h"
#include "Particles/ParticleSystemComponent.h"

ABasicProjectile::ABasicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.005f;

	Visuals = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("body particles"));
	RootComponent = Visuals;

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("hit collider"));
	HitCollider->SetupAttachment(RootComponent);
	HitCollider->OnComponentHit.AddDynamic(this, &ABasicProjectile::OnMeshHit);
}

void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();
	Visuals->ActivateSystem();
	GetWorld()->GetTimerManager().SetTimer(RemainingTTL, this, &ABasicProjectile::Stop, Lifetime, false);
}

void ABasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NextPosition = GetActorLocation() + GetActorForwardVector() * Velocity * DeltaTime;
	SetActorLocation(NextPosition, true); 
}

void ABasicProjectile::OnMeshHit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	AdistanceCharacter* Player = Cast<AdistanceCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Player && OtherActor == Player)
	{
		if (Player->IsAlive())
		{
			FDamageReport NewReport;
			NewReport.DamageValue = Power;
			NewReport.Instigator = this;

			Player->TakeDamage(NewReport);
		}
	}
	Stop();
}

void ABasicProjectile::Stop()
{
	GetWorld()->GetTimerManager().ClearTimer(RemainingTTL);
	Destroy();
}
