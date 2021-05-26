// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RifleRangeShooterCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Interactable.h"
#include "Rifle.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

#define mdebug GEngine->AddOnScreenDebugMessage(INDEX_NONE, 12.f, FColor::Blue, TEXT("ok"));

#define md(x) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 12.f, FColor::Cyan, x);

#define showbelt(player) for(int i = 0; i < player->BeltSize; i++) { md(UKismetStringLibrary::Conv_ObjectToString(player->WeaponBelt[i])); } 


ARifleRangeShooterCharacter::ARifleRangeShooterCharacter()
{
	//PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	/// Creating WeaponBelt
	WeaponBelt = TArray<AWeapon*>();

	WeaponBelt.Empty();

	for (int i = 0; i < BeltSize; i++)
		WeaponBelt.Add(nullptr);
	
}


void ARifleRangeShooterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}


void ARifleRangeShooterCharacter::Tick(float deltaTime)
{
	
}


AWeapon* ARifleRangeShooterCharacter::GetWeapon(int INDEXofWeaponBelt)
{
	if (WeaponBelt.IsValidIndex(INDEXofWeaponBelt))
	{
		return WeaponBelt[INDEXofWeaponBelt];
	}

	return nullptr;
}


AWeapon* ARifleRangeShooterCharacter::GetCurrentWeapon()
{
	return GetWeapon(CurrentWeapon);
}


void ARifleRangeShooterCharacter::NextWeapon()
{
	int cw = CurrentWeapon;

	if (++cw >= BeltSize)
		CurrentWeapon = 0;
	else
		CurrentWeapon++;

	ChooseWeapon(CurrentWeapon);
}


bool ARifleRangeShooterCharacter::isWeaponOnHand()
{
	if (WeaponBelt.IsValidIndex(CurrentWeapon))
	{
		if (GetWeapon(CurrentWeapon) != nullptr)
			return true;
	}
	else
		return false;
	
}


void ARifleRangeShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind Act event
	PlayerInputComponent->BindAction("Act", IE_Pressed, this, &ARifleRangeShooterCharacter::Interact);

	// next weapon
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &ARifleRangeShooterCharacter::NextWeapon);

	// reload
	PlayerInputComponent->BindAction("ReloadWeapon", IE_Pressed, this, &ARifleRangeShooterCharacter::Reload);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ARifleRangeShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARifleRangeShooterCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Bind fire event
	//PlayerInputComponent->BindAxis("Fire", this, &ARifleRangeShooterCharacter::OnFire);

	PlayerInputComponent->BindAxis("Fire", this, &ARifleRangeShooterCharacter::OnFire);
}


void ARifleRangeShooterCharacter::ChooseWeapon(int INDEXofWeaponBelt)
{
	if ((INDEXofWeaponBelt >= 0) && (INDEXofWeaponBelt < BeltSize))
	{
		int Last = CurrentWeapon;

		CurrentWeapon = INDEXofWeaponBelt;

		if ((WeaponBelt.IsValidIndex(CurrentWeapon)) &&
			(WeaponBelt[CurrentWeapon] != nullptr))
		{
			for (int i = 0; i < BeltSize; i++)
			{
				if ((WeaponBelt.IsValidIndex(i)) && (WeaponBelt[i] != nullptr))
					WeaponBelt[i]->SetActorHiddenInGame(true);
			}

			WeaponBelt[CurrentWeapon]->SetActorHiddenInGame(false);
		}
		else
			CurrentWeapon = Last;
	}
}


void ARifleRangeShooterCharacter::PickupWeapon(AWeapon* weapon)
{
	for (int i = 0; i < BeltSize; i++)
	{
		if (WeaponBelt[i] == nullptr)
		{
			WeaponBelt[i] = weapon;

			weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GripPoint");
			
			ChooseWeapon(i);

			return;
		}
	}
	
	return;
}


void ARifleRangeShooterCharacter::OnFire(float val)
{
	if ((val > 0) && (GetCurrentWeapon() != nullptr))
	{
		GetCurrentWeapon()->Use();
	}
}

void ARifleRangeShooterCharacter::Reload()
{
	if (GetCurrentWeapon() != nullptr)
	{
		auto r = Cast<ARifle>(GetCurrentWeapon());

		if (r != nullptr)
		{
			r->Reload();
		}
	}
}


void ARifleRangeShooterCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void ARifleRangeShooterCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}


void ARifleRangeShooterCharacter::Interact()
{
	FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();

	FHitResult result;

	FVector start = FirstPersonCameraComponent->GetComponentLocation();
	FVector end = (ForwardVector * 1500) + start;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	
	FCollisionObjectQueryParams p;
	p.AddObjectTypesToQuery(ECollisionChannel::ECC_EngineTraceChannel1);

	bool ok = GWorld->LineTraceSingleByObjectType(result, start, end, p, params);

	if (ok)
	{
		auto interactable = Cast<AInteractable>(result.GetActor());

		if (interactable)
		{
			interactable->OnInteract(this);
		}		
	}
	else
		DrawDebugLine(GWorld, start, end, FColor::Blue, false, 20.f);
}
