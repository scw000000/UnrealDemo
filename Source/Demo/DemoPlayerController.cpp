// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoPlayerController.h"
#include "BasicCharacter.h"

void ADemoPlayerController::SetupInputComponent( )
{
   Super::SetupInputComponent( );
   InputComponent->BindAxis( "WS", this, &ADemoPlayerController::MoveForward );
   InputComponent->BindAxis( "DA", this, &ADemoPlayerController::MoveRight );
   InputComponent->BindAction( "SPace", IE_Pressed, this, &ADemoPlayerController::Jump );
}

void ADemoPlayerController::MoveForward( float amount )
{
   if( m_ControllingCharacter )
      {
      FVector fwd = m_ControllingCharacter->GetActorForwardVector( );
      m_ControllingCharacter->AddMovementInput( fwd, amount );
      }
}

void ADemoPlayerController::MoveRight( float amount )
{
   if( m_ControllingCharacter )
      {
      FVector right = m_ControllingCharacter->GetActorRightVector( );
      m_ControllingCharacter->AddMovementInput( right, amount );
      }
}

void ADemoPlayerController::Jump( )
{
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->Jump();
      }
}


