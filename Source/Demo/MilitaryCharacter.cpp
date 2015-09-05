// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "MilitaryCharacter.h"

AMilitaryCharacter::AMilitaryCharacter( const FObjectInitializer& ObjectInitializer ) : ABasicCharacter( ObjectInitializer )
{
   PrimaryActorTick.bCanEverTick = false;

   equippedWeapon = WeaponCategories::WeaponCategories_BareHand;
}

void AMilitaryCharacter::ToggleProne( )
{
   WakePlayer();
   if( bodyMotion == BodyMotions::BodyMotions_Idle )
      {
      FVector aimArmRelativeLocation = aimingCamBoom->GetRelativeTransform( ).GetLocation( );
      aimingCamBoom->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, -50.f ) );
      bodyMotion = BodyMotions::BodyMotions_Prone;
      }
   else if( bodyMotion == BodyMotions::BodyMotions_Prone )
      {
      FVector aimArmRelativeLocation = aimingCamBoom->GetRelativeTransform( ).GetLocation( );
      aimingCamBoom->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 70.f ) );
      bodyMotion = BodyMotions::BodyMotions_Idle;
      }
}

void AMilitaryCharacter::StartReload()
{
   if( playerView == PlayerViews::PlayerViews_Aim )
      {
      armMotion = ArmMotions::ArmMotions_IronSightReload;
      }
   else
      {
      armMotion = ArmMotions::ArmMotions_DefaultReload;
      }
}

void AMilitaryCharacter::EndReload()
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

