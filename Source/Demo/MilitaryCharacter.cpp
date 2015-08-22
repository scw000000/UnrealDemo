// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "MilitaryCharacter.h"

AMilitaryCharacter::AMilitaryCharacter( const FObjectInitializer& ObjectInitializer ) : ABasicCharacter( ObjectInitializer )
{
   PrimaryActorTick.bCanEverTick = false;
}

void AMilitaryCharacter::ToggleProne( )
{
   WakePlayer();
   if( m_CurrentBodyMotion == BodyMotions::BodyMotions_Idle )
      {
      FVector aimArmRelativeLocation = m_AimingArm->GetRelativeTransform( ).GetLocation( );
      m_AimingArm->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, -50.f ) );
      m_CurrentBodyMotion = BodyMotions::BodyMotions_Prone;
      }
   else if( m_CurrentBodyMotion == BodyMotions::BodyMotions_Prone )
      {
      FVector aimArmRelativeLocation = m_AimingArm->GetRelativeTransform( ).GetLocation( );
      m_AimingArm->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 70.f ) );
      m_CurrentBodyMotion = BodyMotions::BodyMotions_Idle;
      }
}

void AMilitaryCharacter::Crouch( bool bClientSimulation )
{
   if( m_CurrentBodyMotion != BodyMotions::BodyMotions_Prone )
      {
      Super::Crouch( bClientSimulation );
      }
}

void AMilitaryCharacter::MoveForward( float amount )
{
    if( m_CurrentBodyMotion != BodyMotions::BodyMotions_Prone )
      {
      Super::MoveForward( amount );
      }
}

//custom function for movement
void AMilitaryCharacter::MoveRight( float amount )
{
   if( m_CurrentBodyMotion != BodyMotions::BodyMotions_Prone )
      {
      Super::MoveRight( amount );
      }
}

