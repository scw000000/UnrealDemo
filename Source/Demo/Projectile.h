// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "DemoGame.h"
#include "Projectile.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AProjectile : public AItem
{
	GENERATED_BODY()
public:
	
   AProjectile(const FObjectInitializer& ObjectInitializer );
   void InitVelocity(const FVector& shootDirection);

	UPROPERTY( VisibleAnywhere, Category = Projectile )
      USphereComponent* proxSphere;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Projectile )
      UProjectileMovementComponent* projectileMovement;
private:
   
};
