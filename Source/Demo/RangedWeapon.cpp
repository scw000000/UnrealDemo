// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "RangedWeapon.h"
#include "Projectile.h"

ARangedWeapon::ARangedWeapon()
{
   firingMode = FiringModes::FiringModes_Auto; 
   canFire = true;
   maxAmmo = 30;
}

void ARangedWeapon::OnTriggerPressed()
{
   if( GetcanFire() )
      {
      Fire();

      }
}

void ARangedWeapon::OnTriggerReleased()
{
switch( firingMode )
      {
      case FiringModes::FiringModes_Auto :
         break;
      }
}

void ARangedWeapon::Fire()
{
   if ( projectileClass )
      {
      FVector const nozzleLocation = mesh->GetSocketLocation( "nozzleSocket" );
      FVector const barrelLocation = mesh->GetSocketLocation( "barrelSocket" );
      FRotator nozzleRotation = GetActorRotation();
      UWorld* const World = GetWorld();
      if (World)
         {
         FActorSpawnParameters SpawnParams;
         SpawnParams.Owner = this;
         SpawnParams.Instigator = Instigator;
         // spawn the projectile at the muzzle
         AProjectile* const Projectile = GetWorld()->SpawnActor<AProjectile>(projectileClass, nozzleLocation, nozzleRotation );
            if (Projectile)
            {
            // find launch direction
            FVector LaunchDir = nozzleLocation - barrelLocation;
            LaunchDir.Normalize();
            Projectile->InitVelocity(LaunchDir);
            }
         }
      }
}

void ARangedWeapon::SetcanFire( const bool& inCanFire )
{
   canFire = inCanFire;
}

bool ARangedWeapon::GetcanFire()
{
   return canFire;
}
