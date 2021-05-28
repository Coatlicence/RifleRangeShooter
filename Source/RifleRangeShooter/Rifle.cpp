// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"
#include "Kismet/KismetStringLibrary.h"


#define md(x) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 12.f, FColor::Cyan, x);

ARifle::ARifle()
{
	Name = "Rifle";

	Effect = CreateDefaultSubobject<UParticleSystem>(TEXT("effect"));
	
	ConstructorHelpers::FObjectFinder<UParticleSystem> assetParticleSystem(
		TEXT("ParticleSystem'/Game/FreeAssets/FPS_Weapon_Bundle/Weapons/Materials/BulletTrace.BulletTrace'"));

	if (assetParticleSystem.Succeeded())
	{
		Effect = assetParticleSystem.Object;
	}

	FireModes.clear();

	FireModes.insert(std::make_pair(EFireModes::SINGLE,		[&](float val) { this->SingleFire(val);		}));
	FireModes.insert(std::make_pair(EFireModes::AUTOMATIC,	[&](float val) { this->AutomaticFire(val);	}));
}

void ARifle::Reload()
{
	if (AllAmmo >= MaxAmmoInClip)
	{
		AllAmmo += CurrentAmmoInClip;

		CurrentAmmoInClip = MaxAmmoInClip;

		AllAmmo -= MaxAmmoInClip;

	}
	else
	{
		AllAmmo += CurrentAmmoInClip;

		CurrentAmmoInClip = AllAmmo;

		AllAmmo = 0;
	}
}

void ARifle::Fire()
{
	if ((CanAttack) && (CurrentAmmoInClip > 0))
	{
		CanAttack = false;

		FActorSpawnParameters params;
		FVector loc = WeaponMesh->GetSocketLocation("socket_BulletSpawnPosition");
		FRotator rot = GetActorRotation();

		auto bullet = GetWorld()->SpawnActor<ABullet>(loc, rot, params);

		bullet->AddDamage(Damage);

		GetWorld()->GetTimerManager().SetTimer(attackDelayTimer, this, &ARifle::CanAttackSet, AttackDelay);


		auto sound = AttackSounds[FMath::RandRange(0, AttackSounds.Num() - 1)];
		
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), sound, loc, rot);

		CurrentAmmoInClip--;
	}
}

void ARifle::SingleFire(float val)
{
	if ((val >= 1.f) && (!TriggerIsPulled) && CanAttack) 
	{
		TriggerIsPulled = true;
		Fire();
	}
	
	if (val < 1.f)
	{
		TriggerIsPulled = false;
	}
}

void ARifle::AutomaticFire(float val)
{
	if (val >= 1)
	{
		Fire();
	}
}

void ARifle::Use(float val)
{

	bool expression = FireModes.begin() != FireModes.end();

	if (expression)
	{
		FireModes.at(CurrentFireMode)(val);
	}
}

void ARifle::AddToAllAmmo(uint16 addNumber)
{
	AllAmmo += (int)addNumber;
}

void ARifle::NextFiremode()
{
	std::map<EFireModes, std::function<void(float)>>::const_iterator it;
	it = FireModes.find(CurrentFireMode);

	it++;

	if (it == FireModes.cend())
	{
		it = FireModes.cbegin();
	}

	CurrentFireMode = it->first;
}
