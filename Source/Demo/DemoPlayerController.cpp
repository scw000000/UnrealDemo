// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"
#include "DemoEnums.h"
#include "DemoPlayerController.h"
#include "GameInfo/DemoPlayerState.h"

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
   if( controllingCharacter )
      {
      controllingCharacter->Jump( );
      }
}

void ADemoPlayerController::BPressed( )
{
   if( controllingCharacter )
      {
      controllingCharacter->SetPlayerView( PlayerViews::PlayerViews_FirstPerson );
      }
}

void ADemoPlayerController::BReleased( )
{
   if( controllingCharacter )
      {
      controllingCharacter->SetPlayerView( PlayerViews::PlayerViews_ThirdPerson );
      }
}

void ADemoPlayerController::CPressed( )
{
   if( controllingCharacter )
      {
      controllingCharacter->ToggleProne( );
      }
}

void ADemoPlayerController::RMBPressed( )
{
   if( controllingCharacter )
      {
      controllingCharacter->SetPlayerView( PlayerViews::PlayerViews_Aim );
      }
}

void ADemoPlayerController::RMBReleased( )
{
   if( controllingCharacter )
   {
   controllingCharacter->SetPlayerView( PlayerViews::PlayerViews_ThirdPerson );
   }
}

void ADemoPlayerController::LeftMouseButtonPressed()
{
   if( controllingCharacter )
   {
   controllingCharacter->StartAttack( );
   }
}

void ADemoPlayerController::LeftMouseButtonReleased()
{
   if( controllingCharacter )
   {
   controllingCharacter->StopAttack( );
   }
}

void ADemoPlayerController::LeftCtrlPressed()
{
   if( controllingCharacter )
   {
   controllingCharacter->Crouch( );
   }
}
void ADemoPlayerController::LeftCtrlReleased()
{
   if( controllingCharacter )
   {
   controllingCharacter->UnCrouch();
   }
}


void ADemoPlayerController::MouseWheelUpPressed( )
{
   if( controllingCharacter)
      {
      controllingCharacter->SetCamDistance( 1.f );
      }
}

void ADemoPlayerController::MouseWheelDownPressed( )
{
   if( controllingCharacter)
      {
      controllingCharacter->SetCamDistance( -1.f );
      }
}



void ADemoPlayerController::Possess( APawn * InPawn )
{
   Super::Possess( InPawn );
   ADemoPlayerState* playerState = InPawn ? Cast<ADemoPlayerState>( InPawn->PlayerState ) : NULL;

   if( SetControllingCharacter( InPawn ) )
   {
      playerState->SetTeamNum( 1 );
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "set team sucess" );
   }
   else
   {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "err: possess failed" );
   }
}

bool ADemoPlayerController::SetControllingCharacter( APawn* InPawn )
{
   controllingCharacter = InPawn ? Cast<ABasicCharacter>( InPawn ) : NULL ;
   if( controllingCharacter )
      {
      return true;
      }
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "err: possess cast fail" );
   return false;
}

void ADemoPlayerController::WS( float amount )
{
   if( controllingCharacter && amount )
      {
      controllingCharacter->MoveForward( amount );
      }
}

void ADemoPlayerController::AD( float amount )
{
   if( controllingCharacter && amount )
      {
      controllingCharacter->MoveRight( amount );
      }
}

void ADemoPlayerController::MouseX( float amount )
{
   if( controllingCharacter && amount )
      {
      controllingCharacter->SetCamYaw( amount );
      }
}

void ADemoPlayerController::MouseY( float amount )
{
   if( controllingCharacter && amount )
      {
      controllingCharacter->SetCamPitch( amount );
      }
}






