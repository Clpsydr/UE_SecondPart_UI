// Copyright Epic Games, Inc. All Rights Reserved.
#include "distanceCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "InventoryComponent.h"
#include "EquipComponent.h"
#include "InventoryManagerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "StatusBar.h"
#include "Blueprint/UserWidget.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AdistanceCharacter::AdistanceCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Extra components
	PlayerStats = CreateDefaultSubobject<UStatsComponent>(TEXT("Player Stats"));

	// UI components
	PlayerStatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusBar"));
	PlayerStatusWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	PlayerStatusWidget->SetWidgetClass(StatusWidgetClass);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Attaching inventory and inv manager
	PInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	PInvManager = CreateDefaultSubobject<UInventoryManagerComponent>(TEXT("Inventory Manager"));
	PEquip = CreateDefaultSubobject<UEquipComponent>(TEXT("Equipment"));
}

void AdistanceCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AdistanceCharacter::EquipItem(EEquipType Slot, FName ItemId)
{
	const auto* ItemInfo = PInvManager->GetItemData(ItemId);

	// applying mesh if present
	UStaticMeshComponent* EquippedModel = GetEquipComponent(Slot);
	if (EquippedModel)
	{
		EquippedModel->SetStaticMesh(ItemInfo->Mesh.LoadSynchronous());
		EquippedModel->SetHiddenInGame(false);
	}

	//applying normal stat bonus
	PlayerStats->ApplyStatBonus(ItemInfo);
}

void AdistanceCharacter::UnequipItem(EEquipType Slot, FName ItemId)
{
	UStaticMeshComponent* EquippedModel = GetEquipComponent(Slot);
	if (EquippedModel)
	{
		EquippedModel->SetHiddenInGame(true);
	}

	PlayerStats->RemoveStatBonus(PInvManager->GetItemData(ItemId));
}

UStaticMeshComponent* AdistanceCharacter::GetEquipComponent(EEquipType EquipType)
{
	FName Tag;

	switch (EquipType)
	{
		case EEquipType::Es_Head: Tag = "HeadSlot"; break;
		case EEquipType::Es_Back: Tag = "BackSlot"; break;
		case EEquipType::Es_Belt: Tag = "BeltSlot"; break;
		case EEquipType::Es_Body: Tag = "BodySlot"; break;
		case EEquipType::Es_Weapon: Tag = "WeaponSlot"; break;
		case EEquipType::Es_Buff: Tag = "BuffSlot"; break;
		default: return nullptr;
	}

	TArray<UActorComponent*> SlotFound = GetComponentsByTag(UStaticMeshComponent::StaticClass(), Tag);
	
	// Assuming there is only one equip slot of each type!!!
	return SlotFound.IsValidIndex(0) ? Cast<UStaticMeshComponent>(SlotFound[0]) : nullptr;
}

void AdistanceCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
		// temp shelter for stat updates
	PlayerStats->ModifyHealth(PlayerStats->HPRegen);
	PlayerStats->ArmorUpdate();
		// widget init
	UpdateWidgets();						
	
	if (CursorToWorld != nullptr && IsAlive())
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void AdistanceCharacter::Death()
{
	TArray<USceneComponent*> Skeletons;
	RootComponent->GetChildrenComponents(false, Skeletons);
	for (auto component : Skeletons)
	{
		component->SetHiddenInGame(true);
	}

	GetController()->UnPossess();
}

void AdistanceCharacter::Harm(float Points)
{
	PlayerStats->ModifyHealth(-Points);
	if (!IsAlive())
	{
		Death();
	}
}

void AdistanceCharacter::GenerateItems(const TArray<FEquipSlot>& NewItems)
{
	if (PInvManager)
	{
		GLog->Log(ELogVerbosity::Display, *FString::Printf(TEXT("Got class related items")));
		PInvManager->SupplyItemSet(NewItems, PInventory);
	}
}

bool AdistanceCharacter::IsAlive()
{
	return (PlayerStats->GetHealth(false) > 0);
}

void AdistanceCharacter::OpenChest(UInventoryComponent* ChestInventory)
{
	if (ChestInventory)
	{
		PInvManager->ShowChest(ChestInventory);
	}
	else
	{
		PInvManager->HideChest();
	}
		
}

void AdistanceCharacter::TakeDamage(const FDamageReport& DamageReport)
{
	Harm(DamageReport.DamageValue);
	UpdateWidgets();
}

void AdistanceCharacter::UpdateWidgets()
{
	if (PlayerStatusWidget->GetWidget())
	{
		UStatusBar* Status = Cast<UStatusBar>(PlayerStatusWidget->GetUserWidgetObject());
		Status->UpdateCompact(PlayerStats->GetShortenedParams());
	}
}

