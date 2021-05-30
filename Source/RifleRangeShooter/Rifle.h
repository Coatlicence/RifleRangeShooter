// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>
#include <functional>

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

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float Damage;

protected:
	///---------------------------------------------------
	// Ammo Clip

	UPROPERTY(EditAnywhere, Category = "ABullet")
	int MaxAmmoInClip = 30;

	UPROPERTY(EditAnywhere, Category = "ABullet")
	int CurrentAmmoInClip = 0;

	UPROPERTY(EditAnywhere, Category = "ABullet")
	int AllAmmo = 0;
	
	///--------------------------------------------------
	// fire modes

	enum EFireModes
	{
		AUTOMATIC = 0,
		SINGLE,
		THREE,
		num, // used to determine number of enum member
	};

	EFireModes CurrentFireMode = EFireModes::SINGLE;

	std::map<EFireModes, std::function<void(float)>> FireModes;

	///--------------------------------------------------
	// Recoil

	UPROPERTY(EditAnywhere, Category = "Recoil")
	float Recoil = 0.5;

	UPROPERTY(EditAnywhere, Category = "Recoil")
	float MinInaccuracy = 1.f;

	float MinInaccuracyDynamic = MinInaccuracy;

	UPROPERTY(EditAnywhere, Category = "Recoil")
	float MaxInaccuracy = 3.f;

	float MaxInaccuracyDynamic = MaxInaccuracy;

	/// For EveryTick subracts this value from CurrentInaccuracy
	UPROPERTY(EditAnywhere, Category = "Recoil")
	float RecoilRecovery = 0.02;

	/// How many degresses we will add to bullet rotation
	float CurrentInaccuracy = 0;

	///----------------------------

	bool TriggerIsPulled = false;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	ABullet* bullet;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	UParticleSystem* Effect;

public:
	
	void Reload();

	void Use(float val) override;

	void AddToAllAmmo(uint16 addNumber);

	void NextFiremode();

private:
	/// Firemodes definition

	/// Default method
	virtual void Fire();

	virtual void SingleFire(float val);

	virtual void AutomaticFire(float val);

	
};