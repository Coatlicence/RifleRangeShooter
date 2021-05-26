// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "Interactable.generated.h"

#define ECC_Interactable ECollisionChannel::ECC_GameTraceChannel1

UCLASS(abstract)
class RIFLERANGESHOOTER_API AInteractable : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AInteractable();

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	UBoxComponent* PickupCollision;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(AActor* Caller) PURE_VIRTUAL(AInteractable::OnInteract, );
};
