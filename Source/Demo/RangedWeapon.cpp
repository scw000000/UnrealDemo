// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoGame.h"
#include "RangedWeapon.h"
#include "Projectile.h"
#include "MilitaryCharacter.h"

ARangedWeapon::ARangedWeapon( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
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

bool ARangedWeapon::CanReload()
{
   if( ammo < maxAmmo && bpProjectile )
      {
      return true;
      }
   else 
      {
      return false;
      }
}

void ARangedWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
   crossHairSize -= DeltaTime * crossHairSizeDecrSpeed;
   crossHairSize = FMath::Clamp<float>( crossHairSize, minCrossHairSize, maxCrossHairSize );
}

void ARangedWeapon::Fire( FVector hitPoint )
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
         AProjectile* const Projectile = GetWorld()->SpawnActor<AProjectile>( bpProjectile, nozzleLocation, nozzleRotation, SpawnParams );
         if (Projectile)
            {
            // find launch direction
            FVector LaunchDir = hitPoint - nozzleLocation;
            LaunchDir.Normalize();
            Projectile->InitVelocity( LaunchDir );
            //set ammo num
            ammo--;
            SetisCoolDownOver( false );
            StartCoolDownTimer();
            crossHairSize += crossHairSizeIncrSpeed;
            crossHairSize = FMath::Clamp<float>( crossHairSize, minCrossHairSize, maxCrossHairSize );
            }
         }
      }
}

void ARangedWeapon::Reload( int32 reloadAmmoNum )
{
   ammo = FMath::Clamp<int32>( ammo + reloadAmmoNum, 0, maxAmmo );
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

void ARangedWeapon::OnTriggerPressed()
{
   TryFire( true );
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
//on TriggerPressed indicates that is this is the first shot
//test condition for cooldown
void ARangedWeapon::TryFire( bool onTriggerPressed )
{
   if( isCoolDownOver )
      {
      switch( fireMode )
         {
         case FireModes::FireModes_Auto :
            TryAutoFire();
            break;
         case FireModes::FireModes_SemiAuto :
            TrySemiAutoFire( onTriggerPressed );
            break;
         }
      }
}

void ARangedWeapon::TryAutoFire()
{
   UWorld *const world = GetWorld();
   if( world )
      {
         //keep firing and ignred the cooldown limitation, since the timer already call Fire() based on cooldown time
      world->GetTimerManager().SetTimer( autoFireTimerHandle, this, &ARangedWeapon::TrySingleFire, coolDownTime, true, 0.f );
      }
}

void ARangedWeapon::TrySemiAutoFire( bool onTriggerPressed )
{
   if( onTriggerPressed )
      {
      TrySingleFire();
      }
}
//TrySingleFire should always be called by TryAutoFire() or TrySemiAutoFire() since it negelects isCoolDownOver condition
void ARangedWeapon::TrySingleFire()
{
   AMilitaryCharacter *character = Cast<AMilitaryCharacter>( GetOwner() );
   if( character &&  ammo > 0 )
      {
      UCameraComponent *playerCamera = character->playerCamera;
      FCollisionQueryParams lineTraceParams = FCollisionQueryParams(FName( TEXT( "Line_Trace" ) ), true, this);
      lineTraceParams.bTraceComplex = true;
      lineTraceParams.bTraceAsyncScene = true;
      lineTraceParams.bReturnPhysicalMaterial = false;
      lineTraceParams.AddIgnoredActor( GetOwner() );
 
      FHitResult line_HitResult( ForceInit );

      const FVector traceStart = playerCamera->GetComponentLocation();      
      const FVector traceEnd = traceStart + playerCamera->GetForwardVector() * 4096; 
      bool isHitImpactPointExist = GetWorld()->LineTraceSingleByChannel( 
                                      line_HitResult,        //result
                                      traceStart + playerCamera->GetForwardVector() * 10,    //start
                                      traceEnd, //end
                                      COLLISION_WEAPON,
                                      lineTraceParams
                                      );
       
      if( isHitImpactPointExist )
         {
         Fire( line_HitResult.ImpactPoint );
         }
      else
         {
         Fire( traceEnd );
         }
      }
}

void ARangedWeapon::ResetisCoolDownOver()
{  
   isCoolDownOver = true;
   if( isTriggerOn )
      {
      TryFire( false );
      }
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