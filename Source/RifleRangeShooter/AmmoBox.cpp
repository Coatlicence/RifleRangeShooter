// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"

#define md(x) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 12.f, FColor::Cyan, x);


AAmmoBox::AAmmoBox()
{
	AmmoBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ammo box mesh"));
	AmmoBoxMesh->AttachTo(RootComponent);
	AmmoBoxMesh->SetRelativeLocation(FVector(0.f, 10.f, 0.f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> assetMesh(TEXT("StaticMesh'/Game/FreeAssets/FPS_Weapon_Bundle/AmmoBoxes/Mesh/AmmoBox.AmmoBox'"));

	if (assetMesh.Succeeded())
	{
		AmmoBoxMesh->SetStaticMesh(assetMesh.Object);

	}
}

void AAmmoBox::BeginPlay()
{
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCollision->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);
}

void AAmmoBox::OnInteract(AActor* Caller)
{
	auto player = Cast<ARifleRangeShooterCharacter>(Caller);

	md(TEXT("1"));

	if (player != nullptr)
	{
		auto weapon = player->GetCurrentWeapon();

		auto rifle = Cast<ARifle>(weapon);

		md(TEXT("2"));

		if (rifle != nullptr)
		{
			rifle->AddToAllAmmo(Ammo);

			md(TEXT("ok"));

			Destroy();
		}
	}
}

