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
	/** initial setup */
	virtual void PostInitializeComponents() override;

   AProjectile(const FObjectInitializer& ObjectInitializer );

   void InitVelocity(const FVector& shootDirection);

	/** handle hit */
	UFUNCTION()
	   void OnImpact( const FHitResult& hitResult );

	UPROPERTY( VisibleDefaultsOnly, Category = Projectile )
      USphereComponent* proxSphere;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Projectile )
      UProjectileMovementComponent* projectileMovementComp;

   
private:

   /** trigger explosion */
	void Explode( const FHitResult& hitResult );

   /** controller that fired me (cache for damage calculations) */
	TWeakObjectPtr<AController> controller;

   /** projectile data */
	struct FProjectileConfig projectileConfig;

   bool isExploded;
};
