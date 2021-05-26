// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "RifleRangeShooterCharacter.h"
#include "Rifle.h"
#include "Components/StaticMeshComponent.h"
#include "AmmoBox.generated.h"

/**
 * 
 */
UCLASS()
class RIFLERANGESHOOTER_API AAmmoBox : public AInteractable
{
	GENERATED_BODY()

public:
	AAmmoBox();


	UPROPERTY(EditAnywhere, Category = "Ammo")
	int Ammo;

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* AmmoBoxMesh;

	virtual void BeginPlay() override;

public:
	void OnInteract(AActor* Caller) override;
	

};
