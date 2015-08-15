// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"
#include "DemoPlayerController.h"

void ADemoPlayerController::SetupInputComponent( )
{
   Super::SetupInputComponent( );
   // InputComponent->BindAxis( "MouseX", this, &ADemoPlayerController::Yaw );
   // InputComponent->BindAxis( "MouseY", this, &ADemoPlayerController::Pitch );

   InputComponent->BindAxis( "WS", this, &ADemoPlayerController::WS );
   InputComponent->BindAxis( "AD", this, &ADemoPlayerController::AD );
   InputComponent->BindAxis( "MouseX", this, &ADemoPlayerController::MouseX );
   InputComponent->BindAxis( "MouseY", this, &ADemoPlayerController::MouseY );

   InputComponent->BindAction( "Space", IE_Pressed, this, &ADemoPlayerController::SpacePressed );
   InputComponent->BindAction( "B", IE_Pressed, this, &ADemoPlayerController::BButtonPressed );
   InputComponent->BindAction( "B", IE_Released, this, &ADemoPlayerController::BButtonReleased );
}

void ADemoPlayerController::SpacePressed( )
{
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->Jump( );
      }
}

void ADemoPlayerController::BButtonPressed( )
{
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->SetViewPointToFirstPerson();
      }
}

void ADemoPlayerController::BButtonReleased( )
   {
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->SetViewPointToThirdPerson( );
      }
   }


void ADemoPlayerController::Possess( APawn * InPawn )
{
   Super::Possess( InPawn );
   if( SetControllingCharacter( InPawn ) )
   {

   }
   else
   {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "err: possess failed" );
   }
}

bool ADemoPlayerController::SetControllingCharacter( APawn* InPawn )
{
   ABasicCharacter *character = Cast<ABasicCharacter>( InPawn );

   if( character )
      {
      m_ControllingCharacter = character;
      return true;
      }
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "err: possess cast fail" );
   return false;
}

void ADemoPlayerController::WS( float amount )
{
   if( m_ControllingCharacter && amount )
      {
      m_ControllingCharacter->MoveForward( amount );
      }
}

void ADemoPlayerController::AD( float amount )
{
   if( m_ControllingCharacter && amount )
      {
      m_ControllingCharacter->MoveRight( amount );
      }
}

void ADemoPlayerController::MouseX( float amount )
{
   if( m_ControllingCharacter && amount )
      {
      m_ControllingCharacter->Yaw( amount );
      }
}

void ADemoPlayerController::MouseY( float amount )
{
   if( m_ControllingCharacter && amount )
      {
      m_ControllingCharacter->Pitch( amount );
      }
}




