// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "RifleRangeShooterCharacter.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

#define mdebug GEngine->AddOnScreenDebugMessage(INDEX_NONE, 12.f, FColor::Blue, TEXT("ok"));


// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = "Weapon"; 

	AttackDelay = 0.5f;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	WeaponMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	PickupCollision->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		meshAsset(TEXT("SkeletalMesh'/Game/FreeAssets/FPS_Weapon_Bundle/Weapons/Meshes/AC_Val/SK_AC_Val.SK_AC_Val'"));

	if (meshAsset.Succeeded())
	{
		WeaponMesh->SetSkeletalMesh(meshAsset.Object);
	}

	///----------------------------
	// Sound

	static ConstructorHelpers::FObjectFinder<USoundWave>
		Asset(TEXT("SoundWave'/Game/FreeAssets/FPS_Weapon_Bundle/Weapons/Audio/AC_VAL/AC_VAL_fire1.AC_VAL_fire1'"));
	
	if (Asset.Succeeded())
	{
		AttackSounds.Add(Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundWave>
		Asset1(TEXT("SoundWave'/Game/FreeAssets/FPS_Weapon_Bundle/Weapons/Audio/AC_VAL/AC_VAL_fire2.AC_VAL_fire2'"));
	
	if (Asset1.Succeeded())
	{
		AttackSounds.Add(Asset1.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundWave>
		Asset2(TEXT("SoundWave'/Game/FreeAssets/FPS_Weapon_Bundle/Weapons/Audio/AC_VAL/AC_VAL_fire3.AC_VAL_fire3'"));

	if (Asset2.Succeeded())
	{
		AttackSounds.Add(Asset2.Object);
	}

}

void AWeapon::CanAttackSet()
{
	CanAttack = true;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCollision->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWeapon::OnInteract(AActor* Caller)
{
	auto p = Cast<ARifleRangeShooterCharacter>(Caller);

	if (p != nullptr)
	{
		p->PickupWeapon(this);
	}
}
