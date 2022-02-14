// Fill out your copyright notice in the Description page of Project Settings.
#include "Locator.h"
#include "distanceCharacter.h"
#include "InventoryComponent.h"
#include "Components/BoxComponent.h"

ALocator::ALocator()
{
	ChestOpenArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Chest vicinity"));
	ChestOpenArea->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ChestOpenArea->OnComponentBeginOverlap.AddDynamic(this, &ALocator::OnMeshOverlapBegin);
	ChestOpenArea->OnComponentEndOverlap.AddDynamic(this, &ALocator::OnMeshOverlapEnd);

	EInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}


void ALocator::BeginPlay()
{
	Super::BeginPlay();
}

void ALocator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALocator::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == PlayerPawn && OtherComp && !bIsOpen)
	{
		Cast<AdistanceCharacter>(PlayerPawn)->OpenChest(EInventory);
		bIsOpen = true;
	}
}

void ALocator::OnMeshOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	if (OtherActor == PlayerPawn)
	{
		Cast<AdistanceCharacter>(PlayerPawn)->OpenChest(nullptr);
		bIsOpen = false;
	}
}
