// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"
#include "BasicPlayerController.h"

void ABasicPlayerController::BeginPlay( )
{
   Super::BeginPlay( );
   SetControllingCharacter( Cast<ABasicCharacter>( GetPawn( ) ) );

   if( !m_ControllingCharacter )
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "error:null character pointer" );
}

void ABasicPlayerController::Possess( APawn * InPawn )
{
   if( SetControllingCharacter( InPawn ) )
      {
      Super::Possess( InPawn );
    //  m_Camera->AttachTo( m_CameraBoomPitch );
    //  m_Camera->bUsePawnControlRotation = false;
      SetViewTarget( this );
      //   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess " );
      }
   else
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess failed" );
      }
}

bool ABasicPlayerController::SetControllingCharacter( APawn* InPawn )
{
   ABasicCharacter *character = Cast<ABasicCharacter>( InPawn );

   if( character )
      {
      m_ControllingCharacter = character;
      return true;
      }
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess cast fail" );
   return false;
}


