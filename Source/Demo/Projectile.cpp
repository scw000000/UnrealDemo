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
   projectileMovementComp->Bounciness  = 0.f;

   isExploded = false;
}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	projectileMovementComp->OnProjectileStop.AddDynamic( this, &AProjectile::OnImpact );
	//proxSphere->MoveIgnoreActors.Add( Instigator );
	controller = GetInstigatorController();
   ARangedWeapon* ownerWeapon = Cast<ARangedWeapon>( GetOwner() );
	if ( ownerWeapon )
	{
		ownerWeapon->ApplyProjectileConfig ( projectileConfig );
	}
   SetLifeSpan( projectileConfig.projectileLife );
}

void AProjectile::InitVelocity( const FVector & shootDirection )
{
   if ( projectileMovementComp )
      {
      projectileMovementComp->InitialSpeed = projectileConfig.projectileVelocity;
      projectileMovementComp->MaxSpeed = projectileConfig.projectileVelocity;
      projectileMovementComp->Velocity = shootDirection * projectileConfig.projectileVelocity;
      }
}

void AProjectile::OnImpact( const FHitResult& hitResult )
{
	if ( !isExploded )
	   {
		Explode( hitResult );
		//DisableAndDestroy();
	   }
   isExploded = true;
}

void AProjectile::Explode( const FHitResult& hitResult )
{

	// effects and damage origin shouldn't be placed inside mesh at impact point
	const FVector nudgedImpactLocation = hitResult.ImpactPoint + hitResult.ImpactNormal * 10.0f;
	if ( projectileConfig.explosionDamage > 0 && projectileConfig.explosionRadius > 0 && projectileConfig.damageType )
	   {
	//	UGameplayStatics::ApplyRadialDamage( this, projectileConfig.explosionDamage, nudgedImpactLocation, projectileConfig.explosionRadius, projectileConfig.damageType, TArray<AActor*>(), controller->GetPawn(), controller.Get() );
	UGameplayStatics::ApplyRadialDamage( this, projectileConfig.explosionDamage, nudgedImpactLocation, projectileConfig.explosionRadius, projectileConfig.damageType, TArray<AActor*>(), NULL, controller.Get() );

      //  UGameplayStatics::
      }

	isExploded = true;
}


