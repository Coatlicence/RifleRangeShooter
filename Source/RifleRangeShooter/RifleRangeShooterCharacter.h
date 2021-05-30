// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "RifleRangeShooterCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class ARifleRangeShooterCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	ARifleRangeShooterCharacter();

protected:
	virtual void BeginPlay();

	virtual void Tick(float deltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TArray<AWeapon*> WeaponBelt;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int BeltSize = 3;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int CurrentWeapon = 0;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


protected:

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);
	

	/// Interacts with InterfaceInteractable
	void Interact();

	///---------------------------------------------------------------------------
	// Working with weapon

	// uses a projectile. 
	void OnFire(float val);

	void Reload();

	void NextWeapon();

	void NextFiremode();

	void ChooseWeapon(int INDEXofWeaponBelt);

	void ThrowCurrentWeapon();

	FORCEINLINE AWeapon* GetWeapon(int INDEXofWeaponBelt);

	FORCEINLINE bool isWeaponOnHand();

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	AWeapon* GetCurrentWeapon();

	void PickupWeapon(AWeapon* weapon);

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

