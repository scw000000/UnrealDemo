// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "Projectile.h"

AProjectile::AProjectile( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
 	
   proxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
   proxSphere->InitSphereRadius( 15.0f );
   RootComponent = proxSphere;
   mesh->AttachTo( RootComponent );

   projectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
   projectileMovement->UpdatedComponent = RootComponent;
   projectileMovement->InitialSpeed = 3000.f;
   projectileMovement->MaxSpeed = 3000.f;
   projectileMovement->bRotationFollowsVelocity = true;
   projectileMovement->bShouldBounce = true;
   projectileMovement->Bounciness  = 0.3f;
}

void AProjectile::InitVelocity( const FVector & shootDirection )
{
   if ( projectileMovement )
      {
      projectileMovement->Velocity = shootDirection * projectileMovement->InitialSpeed;
      }
}


