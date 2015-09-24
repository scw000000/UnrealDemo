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

   projectileMovementComp = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileMovementComp"));
   projectileMovementComp->UpdatedComponent = RootComponent;
   projectileMovementComp->InitialSpeed = 3000.f;
   projectileMovementComp->MaxSpeed = 3000.f;
   projectileMovementComp->bRotationFollowsVelocity = true;
   projectileMovementComp->bShouldBounce = false;
   projectileMovementComp->Bounciness  = 0.3f;

   isExploded = false;
}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	projectileMovementComp->OnProjectileStop.AddDynamic( this, &AProjectile::OnImpact );
	proxSphere->MoveIgnoreActors.Add( Instigator );

	controller = GetInstigatorController();
}

void AProjectile::InitVelocity( const FVector & shootDirection )
{
   if ( projectileMovementComp )
      {
      projectileMovementComp->Velocity = shootDirection * projectileMovementComp->InitialSpeed;
      }
}

void AProjectile::OnImpact( const FHitResult& hitResult )
{
	if ( Role == ROLE_Authority && !isExploded )
	{
		Explode( hitResult );
		//DisableAndDestroy();
	}
}

void AProjectile::Explode( const FHitResult& hitResult )
{

	// effects and damage origin shouldn't be placed inside mesh at impact point
	const FVector nudgedImpactLocation = hitResult.ImpactPoint + hitResult.ImpactNormal * 10.0f;

	//if ( WeaponConfig.ExplosionDamage > 0 && WeaponConfig.ExplosionRadius > 0 && WeaponConfig.DamageType )
//	{
		UGameplayStatics::ApplyRadialDamage( this, 10.f, nudgedImpactLocation, 90.f, NULL, TArray<AActor*>(), this, controller.Get() );
	//}

	isExploded = true;
}


