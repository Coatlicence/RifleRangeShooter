// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "ConstructorHelpers.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh->AttachTo(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> assetMesh(TEXT("StaticMesh'/Game/FreeAssets/Geometry/Meshes/1M_Cube.1M_Cube'"));

	if (assetMesh.Succeeded())
	{
		Mesh->SetStaticMesh(assetMesh.Object);
		Mesh->SetRelativeScale3D(FVector(5, 0.5f, 5));
		
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Mesh->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
		Mesh->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Overlap);
	}

	HP = 100;
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel2);
	Mesh->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Overlap);
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

