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

   InputComponent->BindAction( "RightMouseButton", IE_Pressed, this, &ADemoPlayerController::RMBPressed );
   InputComponent->BindAction( "RightMouseButton", IE_Released, this, &ADemoPlayerController::RMBReleased );

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
      m_ControllingCharacter->SetViewType( PlayerViewTypes::PlayerViewTypes_FirstPerson );
      }
}

void ADemoPlayerController::BReleased( )
{
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->SetViewType( PlayerViewTypes::PlayerViewTypes_ThirdPerson );
      }
}

void ADemoPlayerController::RMBPressed( )
{
   if( m_ControllingCharacter )
      {
      m_ControllingCharacter->SetViewType( PlayerViewTypes::PlayerViewTypes_Aim );
      }
}

void ADemoPlayerController::RMBReleased( )
{
   if( m_ControllingCharacter )
   {
   m_ControllingCharacter->SetViewType( PlayerViewTypes::PlayerViewTypes_ThirdPerson );
   }
}

void ADemoPlayerController::MouseWheelUpPressed( )
{
   if( m_ControllingCharacter)
      {
      m_ControllingCharacter->SetCameraDistance( 1.f );
      }
}

void ADemoPlayerController::MouseWheelDownPressed( )
{
   if( m_ControllingCharacter)
      {
      m_ControllingCharacter->SetCameraDistance( -1.f );
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
      m_ControllingCharacter->SetCameraYaw( amount );
      }
}

void ADemoPlayerController::MouseY( float amount )
{
   if( m_ControllingCharacter && amount )
      {
      m_ControllingCharacter->SetCameraPitch( amount );
      }
}






