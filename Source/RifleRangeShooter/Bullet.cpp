// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "RifleRangeShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"




// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> assetBullet(
		TEXT("StaticMesh'/Game/FreeAssets/FPS_Weapon_Bundle/Weapons/Meshes/Ammunition/SM_Shell_762x39.SM_Shell_762x39'"));

	if (assetBullet.Succeeded())
	{
		BulletMesh->SetStaticMesh(assetBullet.Object);
		BulletMesh->AddLocalRotation(FQuat(FRotator(0.f, 270.f, 0.f)));
		BulletMesh->SetWorldScale3D(FVector(3.f));

		BulletMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		//BulletMesh->SetCollision
	}

	BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

	Damage = 25;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector(0, 100000, 0));
	ProjectileMovementComponent->InitialSpeed = 1000;
	
	BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	BulletMesh->IgnoreActorWhenMoving(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn(), true);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//md(TEXT("ok"));
	
	
}

void ABullet::AddDamage(float ToAdd)
{
	Damage += abs(ToAdd);
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != NULL))
	{
		auto target = Cast<ATarget>(OtherActor);

		if (target != nullptr)
		{
			target->HP -= this->Damage;

			if (target->HP <= 0)
				target->Destroy();
		}

		Destroy();
	}
}

