// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"
#include "BasicPlayerController.h"

void ABasicPlayerController::PostInitializeComponents( )
{
   Super::PostInitializeComponents( );
   
}

void ABasicPlayerController::BeginPlay( )
{
   Super::BeginPlay( );
}

void ABasicPlayerController::Possess( APawn * InPawn )
{
   Super::Possess( InPawn );
   if( SetControllingCharacter( InPawn ) )
      {
      SetViewTarget( this );
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


