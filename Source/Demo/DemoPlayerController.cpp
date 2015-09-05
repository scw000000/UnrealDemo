// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"
#include "DemoEnums.h"
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
  // InputComponent->BindAxis( "MouseWheelUp", this, &ADemoPlayerController::MouseScroll );

   InputComponent->BindAction( "Space", IE_Pressed, this, &ADemoPlayerController::SpacePressed );

   InputComponent->BindAction( "B", IE_Pressed, this, &ADemoPlayerController::BPressed );
   InputComponent->BindAction( "B", IE_Released, this, &ADemoPlayerController::BReleased );

   InputComponent->BindAction( "C", IE_Pressed, this, &ADemoPlayerController::CPressed );

   InputComponent->BindAction( "RightMouseButton", IE_Pressed, this, &ADemoPlayerController::RMBPressed );
   InputComponent->BindAction( "RightMouseButton", IE_Released, this, &ADemoPlayerController::RMBReleased );

   InputComponent->BindAction( "LMB", IE_Pressed, this, &ADemoPlayerController::LeftMouseButtonPressed );
   InputComponent->BindAction( "LMB", IE_Released, this, &ADemoPlayerController::LeftMouseButtonReleased );

   InputComponent->BindAction( "LeftCtrl", IE_Pressed, this, &ADemoPlayerController::LeftCtrlPressed );
   InputComponent->BindAction( "LeftCtrl", IE_Released, this, &ADemoPlayerController::LeftCtrlReleased );

   InputComponent->BindAction( "MouseWheelUp", IE_Pressed, this, &ADemoPlayerController::MouseWheelUpPressed );
   InputComponent->BindAction( "MouseWheelDown", IE_Pressed, this, &ADemoPlayerController::MouseWheelDownPressed );

   

}

void ADemoPlayerController::SpacePressed( )
{
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->Jump( );
      }
}

void ADemoPlayerController::BPressed( )
{
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->SetPlayerView( PlayerViews::PlayerViews_FirstPerson );
      }
}

void ADemoPlayerController::BReleased( )
{
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->SetPlayerView( PlayerViews::PlayerViews_ThirdPerson );
      }
}

void ADemoPlayerController::CPressed( )
{
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->ToggleProne( );
      }
}

void ADemoPlayerController::RMBPressed( )
{
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->SetPlayerView( PlayerViews::PlayerViews_Aim );
      }
}

void ADemoPlayerController::RMBReleased( )
{
   if( m_ControllingCharacter )
   {
   m_ControllingCharacter->SetPlayerView( PlayerViews::PlayerViews_ThirdPerson );
   }
}

void ADemoPlayerController::LeftMouseButtonPressed()
{
   if( m_ControllingCharacter )
   {
   m_ControllingCharacter->StartAttack( );
   }
}

void ADemoPlayerController::LeftMouseButtonReleased()
{
   if( m_ControllingCharacter )
   {
   m_ControllingCharacter->EndAttack( );
   }
}

void ADemoPlayerController::LeftCtrlPressed()
{
   if( m_ControllingCharacter )
   {
   m_ControllingCharacter->Crouch( );
   }
}
void ADemoPlayerController::LeftCtrlReleased()
{
   if( m_ControllingCharacter )
   {
   m_ControllingCharacter->UnCrouch();
   }
}


void ADemoPlayerController::MouseWheelUpPressed( )
{
   if( m_ControllingCharacter)
      {
      m_ControllingCharacter->SetCamDistance( 1.f );
      }
}

void ADemoPlayerController::MouseWheelDownPressed( )
{
   if( m_ControllingCharacter)
      {
      m_ControllingCharacter->SetCamDistance( -1.f );
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
      m_ControllingCharacter->SetCamYaw( amount );
      }
}

void ADemoPlayerController::MouseY( float amount )
{
   if( m_ControllingCharacter && amount )
      {
      m_ControllingCharacter->SetCamPitch( amount );
      }
}






