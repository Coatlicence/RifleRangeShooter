// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Particles/ParticleSystemComponent.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class RIFLERANGESHOOTER_API ARifle : public AWeapon
{
	GENERATED_BODY()
	
public:
	ARifle();

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float Damage;

protected:
	///---------------------------------------------------
	// Ammo Clip

	int MaxAmmoInClip = 30;

	int CurrentAmmoInClip = 0;

	int AllAmmo = 0;
	
public:
	void Reload();

public:
	void Use() override;

	void AddToAllAmmo(uint16 addNumber);

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	ABullet* bullet;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	UParticleSystem* Effect;

};
