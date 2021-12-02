#include "EnemyPawn.h"
#include "BasicProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "StatusBar.h"
#include "Blueprint/UserWidget.h"
#include "distanceCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AEnemyPawn::AEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.05f;
	
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("unit body"));
	RootComponent = BodyMesh;

	ProjectileSource = CreateDefaultSubobject<UArrowComponent>(TEXT("firing source"));
	ProjectileSource->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("hit collider"));
	HitCollider->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);

	CurrentHealth = MaxHealth;

	StatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusBar"));
	StatusWidget->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
	StatusWidget->SetWidgetClass(StatusWidgetClass);
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	bIsReadyToFire = true;
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	

	if (StatusWidget->GetWidget())
	{
		UStatusBar* Status = Cast<UStatusBar>(StatusWidget->GetUserWidgetObject());
		Status->UpdateName(ProvisionalName);
	}
}

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerPawn && bIsReadyToFire && Cast<AdistanceCharacter>(PlayerPawn)->IsAlive())
	{
		// give it a rotation to position of playerpawn
		FRotator NewAngle = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
		NewAngle.Pitch = BodyMesh->GetComponentRotation().Pitch;
		NewAngle.Roll = BodyMesh->GetComponentRotation().Roll;
		ProjectileSource->SetWorldRotation(NewAngle);

		if (FVector::DistSquared(PlayerPawn->GetActorLocation(), GetActorLocation()) < FMath::Square(FireRange))
			{
				Fire();
			}
	}

	//temporarily deteriorating to show the change in health
	if (CurrentHealth > 0.f)
	{
		CurrentHealth -= DeltaTime;
	}
	else
	{
		Destroy();
	}

	UpdateWidgets();
}

void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyPawn::Fire()
{
	bIsReadyToFire = false;

	ABasicProjectile* NewBullet;

	NewBullet = GetWorld()->SpawnActor<ABasicProjectile>(ProjectileType, ProjectileSource->GetComponentLocation(), ProjectileSource->GetComponentRotation());
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AEnemyPawn::Reload, ReloadTime, false);
}

void AEnemyPawn::Reload()
{
	bIsReadyToFire = true;
}

void AEnemyPawn::UpdateWidgets()
{
	if (StatusWidget->GetWidget())
	{
		UStatusBar* Status = Cast<UStatusBar>(StatusWidget->GetUserWidgetObject());
		Status->UpdateHP(CurrentHealth / MaxHealth);
	}
}