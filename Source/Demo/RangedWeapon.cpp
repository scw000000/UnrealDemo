// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "RangedWeapon.h"
#include "Projectile.h"

ARangedWeapon::ARangedWeapon()
{
   fireMode = FireModes::FireModes_Auto; 
   maxAmmo = 30;
   fireRate = 60.0;
   canFire = true;
   isTriggerOn = false;
   isCoolDownOver = true;
}

void ARangedWeapon::BeginPlay()
{
	Super::BeginPlay();
   //these vars depends on other vars, need to be set in here since the dependent vars may be modified in BP.
   coolDownTime = 1 / fireRate * 60.f;
   ammo = maxAmmo;
}

void ARangedWeapon::Fire()
{
   if ( bpProjectile )
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
         AProjectile* const Projectile = GetWorld()->SpawnActor<AProjectile>( bpProjectile, nozzleLocation, nozzleRotation );
         if (Projectile)
            {
            // find launch direction
            FVector LaunchDir = nozzleLocation - barrelLocation;
            LaunchDir.Normalize();
            Projectile->InitVelocity( LaunchDir );
            //set ammo num
            ammo--;
            StartCoolDownTimer();
            SetisCoolDownOver( false );
            }
         }
      }
}

void ARangedWeapon::Reload()
{
   
}

void ARangedWeapon::SetcanFire( const bool& inCanFire )
{
   canFire = inCanFire;
}

//set trigger on/off, also detect trigger transition state
void ARangedWeapon::SetisTriggerOn( const bool& isSwitchedOn )
{
   if( isTriggerOn != isSwitchedOn)
      {
      isTriggerOn = isSwitchedOn;
      if( isSwitchedOn )
         {
         OnTriggerPressed();
         }
      else
         {
         OnTriggerReleased();
         }
      }
}

bool ARangedWeapon::GetcanFire()
{
   return canFire;
}


void ARangedWeapon::OnTriggerPressed()
{
   UWorld *const world = GetWorld();
   if( world )
      {
      switch( fireMode )
         {
         case FireModes::FireModes_Auto :
            TryAutoFire();
            break;
         case FireModes::FireModes_SemiAuto :
            TrySemiAutoFire();
          //  world->GetTimerManager().SetTimer( autoFireTimerHandle, this, &ARangedWeapon::TrySingleFire, 1.f / fireRate, false, 0.f );
            break;
         }
      }
}

void ARangedWeapon::OnTriggerReleased()
{ 
   if( fireMode == FireModes::FireModes_Auto )
      {
      UWorld *const world = GetWorld();
      if( world )
         {
         world->GetTimerManager().ClearTimer( autoFireTimerHandle );
         }
      }
}

void ARangedWeapon::TryAutoFire()
{
   //test cool down time since last time released trigger
   if( ammo > 0 && isCoolDownOver)
      {
      UWorld *const world = GetWorld();
      if( world )
         {
         //keep firing and ignred the cooldown limitation, since the timer already call Fire() based on cooldown time
         world->GetTimerManager().SetTimer( autoFireTimerHandle, this, &ARangedWeapon::TrySingleFire, coolDownTime, true, 0.f );
         }
      }
   else
      {
      }
}

void ARangedWeapon::TrySemiAutoFire()
{
   if( ammo > 0 && isCoolDownOver )
      {
      TrySingleFire();
      }
   else
      {
      
      }
}
//TrySingleFire should always be called by TryAutoFire() or TrySemiAutoFire() since it negelects isCoolDownOver condition
void ARangedWeapon::TrySingleFire()
{
   if( ammo > 0 )
      {
      Fire();
      }
}

void ARangedWeapon::ResetisCoolDownOver()
{  
   isCoolDownOver = true;
}

void ARangedWeapon::StartCoolDownTimer()
{
   UWorld *const world = GetWorld();
   if( world )
      {
      world->GetTimerManager().SetTimer( coolDownTimerHandle, this, &ARangedWeapon::ResetisCoolDownOver, coolDownTime, false );
      }
}

void ARangedWeapon::SetisCoolDownOver( bool isOver )
{
   isCoolDownOver = isOver;
}