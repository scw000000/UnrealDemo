// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "RangedWeapon.h"
#include "MilitaryCharacter.h"

AMilitaryCharacter::AMilitaryCharacter( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
   PrimaryActorTick.bCanEverTick = false;

   equippedWeapon = WeaponCategories::WeaponCategories_BareHand;
}

void AMilitaryCharacter::PostInitializeComponents( )
{
   Super::PostInitializeComponents();
}  

void AMilitaryCharacter::BeginPlay()
{
	Super::BeginPlay();
   inventoryManager.SetControllingCharacter( this );
}

void AMilitaryCharacter::ToggleProne( )
{
   WakePlayer();
   if( bodyMotion == BodyMotions::BodyMotions_Idle )
      {
      FVector aimArmRelativeLocation = aimingCameraBoom->GetRelativeTransform( ).GetLocation( );
      aimingCameraBoom->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, -50.f ) );
      bodyMotion = BodyMotions::BodyMotions_Prone;
      }
   else if( bodyMotion == BodyMotions::BodyMotions_Prone )
      {
      FVector aimArmRelativeLocation = aimingCameraBoom->GetRelativeTransform( ).GetLocation( );
      aimingCameraBoom->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 70.f ) );
      bodyMotion = BodyMotions::BodyMotions_Idle;
      }
}

void AMilitaryCharacter::StartAttack()
{
   Super::StartAttack();
   inventoryManager.SetAttack( true );
}

void AMilitaryCharacter::StopAttack()
{
   Super::StopAttack();
   inventoryManager.SetAttack( false );
}

void AMilitaryCharacter::StartReloadWeapon()
{
   if( inventoryManager.CanReload() ){
      if( playerView == PlayerViews::PlayerViews_Aim )
         {
         armMotion = ArmMotions::ArmMotions_IronSightReload;
         }
      else
         {
         armMotion = ArmMotions::ArmMotions_DefaultReload;
         }
      }
}

void AMilitaryCharacter::CatchAnimNotifies()
{
   if( GetMesh() )
      {
      for( TArray<const struct FAnimNotifyEvent *>::TIterator it = GetMesh()->AnimScriptInstance->AnimNotifies.CreateIterator(); it; ++it )
         {
         FString animNotifyName = (*it)->NotifyName.ToString();
         if( animNotifyName.Equals( "EquipSync" ) )
            {
            EquipWeaponAnimSync();
            }
         else if( animNotifyName.Equals( "EquipEnd" ) )
            {
            EndEquipWeapon();
            }
         else if( animNotifyName.Equals( "ReloadSync" ) )
            {
            ReloadWeaponAnimSync();
            }
         else if( animNotifyName.Equals( "ReloadEnd" ) )
            {
            EndReloadWeapon();
            }
         }
      }
   else 
      {
      GEngine->AddOnScreenDebugMessage( -1, 1.0f, FColor::Red, "NO mesh" );
      }
}

void AMilitaryCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
   if( Cast<APlayerController>( GetController() ) )
      {
    //  inventoryManager.ShowBackpack();
      }
}

void AMilitaryCharacter::MoveForward( float amount )
{
    if( bodyMotion != BodyMotions::BodyMotions_Prone )
      {
      Super::MoveForward( amount );
      }
}

//custom function for movement
void AMilitaryCharacter::MoveRight( float amount )
{
   if( bodyMotion != BodyMotions::BodyMotions_Prone )
      {
      Super::MoveRight( amount );
      }
}

void AMilitaryCharacter::Crouch( bool bClientSimulation )
{
   if( bodyMotion != BodyMotions::BodyMotions_Prone )
      {
      Super::Crouch( bClientSimulation );
      }
}

void AMilitaryCharacter::StartEquipWeapon( TSubclassOf<class AWeapon> weapon )
{
   if( playerView == PlayerViews::PlayerViews_ThirdPerson && 
        ( bodyMotion == BodyMotions::BodyMotions_Idle || 
          bodyMotion == BodyMotions::BodyMotions_Jog || 
          bodyMotion == BodyMotions::BodyMotions_CrouchIdle || 
          bodyMotion == BodyMotions::BodyMotions_CrouchJog ) )
      {
      if( inventoryManager.CanEquipWeapon( weapon ) ) 
         {
         inventoryManager.SetEquippingWeapon( weapon );
         this->equippedWeapon = WeaponCategories::WeaponCategories_Rifle;
         armMotion = ArmMotions::ArmMotions_Equip;
         }
      }
}

void AMilitaryCharacter::AddBackpackItemByInstance( AItem *const itemInstance )
{
   inventoryManager.AddBackpackItemByInstance( itemInstance );
}

void AMilitaryCharacter::AddBackpackItemByClass( TSubclassOf<class AItem> itemClass, int32 itemNum )
{
   inventoryManager.AddBackpackItemByClass( itemClass, itemNum );
}

AWeapon* AMilitaryCharacter::GetEquippedWeapon()
{
   return inventoryManager.GetEquippedWeapon();
}

void AMilitaryCharacter::ReloadWeaponAnimSync()
{
   inventoryManager.ReloadWeapon();
}

void AMilitaryCharacter::EndReloadWeapon()
{
   
   if( playerView == PlayerViews::PlayerViews_Aim )
      {
      armMotion = ArmMotions::ArmMotions_IronSight;
      }
   else
      {
      armMotion = ArmMotions::ArmMotions_Default;
      }
}

void AMilitaryCharacter::EndEquipWeapon( )
{ 
   if( playerView == PlayerViews::PlayerViews_Aim )
      {
      armMotion = ArmMotions::ArmMotions_IronSight;
      }
   else
      {
      armMotion = ArmMotions::ArmMotions_Default;
      }

}

void AMilitaryCharacter::EquipWeaponAnimSync()
{           
//GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "equip sync" );
   inventoryManager.EquipWeapon();
   
}

