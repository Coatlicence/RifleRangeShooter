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

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float Damage;

protected:
	///---------------------------------------------------
	// Ammo Clip

	int MaxAmmoInClip = 30;

	int CurrentAmmoInClip = 0;

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

	//virtual void AutoFire();
};