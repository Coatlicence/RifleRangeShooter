// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Target.h"
#include "TimerManager.h"
#include "Bullet.generated.h"

UCLASS()
class RIFLERANGESHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	UStaticMeshComponent* BulletMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	float Damage;

private:
	float LifeTime = 2.f;

	FTimerHandle LifeTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// <param name="ToAdd"> func will use abd() on this var</param>
	void AddDamage(float ToAdd);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitActor, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DestroySelf();
};
