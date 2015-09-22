// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "Projectile.h"

AProjectile::AProjectile( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
 	
   proxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
   proxSphere->InitSphereRadius( 15.0f );
   proxSphere->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
	proxSphere->SetCollisionObjectType( COLLISION_PROJECTILE );
	proxSphere->SetCollisionResponseToAllChannels( ECR_Ignore );
	proxSphere->SetCollisionResponseToChannel( ECC_WorldStatic, ECR_Block );
	proxSphere->SetCollisionResponseToChannel( ECC_WorldDynamic, ECR_Block );
	proxSphere->SetCollisionResponseToChannel( ECC_Pawn, ECR_Block );
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


