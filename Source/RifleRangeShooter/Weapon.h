// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interactable.h"
#include "Engine/World.h"
#include "Sound/SoundBase.h"
#include "Weapon.generated.h"

UCLASS(abstract)
class RIFLERANGESHOOTER_API AWeapon : public AInteractable
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditAnywhere, Category = "Name")
	FString Name;

protected:
	FTimerHandle attackDelayTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	///---------------------------------------------------------
	// Attack

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float AttackDelay;

	bool CanAttack = true;

	void CanAttackSet();

	//UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TArray<USoundBase*> AttackSounds;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void OnInteract(AActor* Caller) override;

	virtual void Use() PURE_VIRTUAL(AWeapon::Use, );

	void OnInteract(AActor* Caller) override;
};