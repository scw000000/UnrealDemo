// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "MoveablePlayerController.h"
#include "BasicCharacter.h"

void AMoveablePlayerController::SetupInputComponent( )
{
   Super::SetupInputComponent( );
   InputComponent->BindAxis( "Forward", this, &AMoveablePlayerController::MoveForward );
   InputComponent->BindAxis( "Strafe", this, &AMoveablePlayerController::MoveRight );
}

void AMoveablePlayerController::MoveForward( float amount )
{
   if( m_ControllingCharacter )
      {
      FVector fwd = m_ControllingCharacter->GetActorForwardVector( );
      m_ControllingCharacter->AddMovementInput( fwd, amount );
      }
}

void AMoveablePlayerController::MoveRight( float amount )
{
   if( m_ControllingCharacter )
      {
      FVector right = m_ControllingCharacter->GetActorRightVector( );
      m_ControllingCharacter->AddMovementInput( right, amount );
      }
}


