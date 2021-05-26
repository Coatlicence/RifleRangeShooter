// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComponent;

	PickupCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Pickup Collision"));
	PickupCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	PickupCollision->SetBoxExtent(FVector(100.f, 50.f, 30.f));
	PickupCollision->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();

	PickupCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	PickupCollision->SetCollisionObjectType(ECC_PhysicsBody);
	PickupCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);

}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

