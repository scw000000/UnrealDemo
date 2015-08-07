// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "ViewablePlayerController.h"
#include "BasicCharacter.h"

AViewablePlayerController::AViewablePlayerController( const FObjectInitializer& ObjectInitializer )
{
   PrimaryActorTick.bCanEverTick = true;

   m_Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>( this, TEXT( "Player Camera" ) );
   m_CameraBoomYaw = NULL;
   m_CameraBoomPitch = NULL;
}

void AViewablePlayerController::SetupInputComponent( )
{
   Super::SetupInputComponent( );
   InputComponent->BindAxis( "Yaw", this, &AViewablePlayerController::Yaw );
   InputComponent->BindAxis( "Pitch", this, &AViewablePlayerController::Pitch );
}

void AViewablePlayerController::BeginPlay( )
{
   Super::BeginPlay( );
   SetControllingCharacter( Cast<ABasicCharacter>( GetPawn( ) ) );

   if( !m_ControllingCharacter )
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "error:null character pointer" );
}

void AViewablePlayerController::Possess( APawn * InPawn )
{
   if( SetControllingCharacter( InPawn ) )
      {
      Super::Possess( InPawn );
      m_Camera->AttachTo( m_CameraBoomPitch );
      m_Camera->bUsePawnControlRotation = false;
      SetViewTarget( this );
      //   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess " );
      }
   else
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess failed" );
      }
}

void AViewablePlayerController::CalcCamera( float DeltaTime, struct FMinimalViewInfo& OutResult )
{
   m_Camera->GetCameraView( DeltaTime, OutResult );
}

void AViewablePlayerController::Tick( float DeltaTime )
{
   Super::Tick( DeltaTime );
}
//needs to disable "use pawn contorl rotation" in spring arm->camera settings
void AViewablePlayerController::Yaw( float amount )
{
//m_ControllingCharacter->m_SpringArm->Add
  // AddYawInput( 200.f * amount * GetWorld( )->GetDeltaSeconds( ) );
m_CameraBoomYaw->AddRelativeRotation( FRotator( 0, 200.f * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );

}

void AViewablePlayerController::Pitch( float amount )
{
m_CameraBoomPitch->AddRelativeRotation( FRotator( 200.f * amount * -1.f * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::SanitizeFloat( m_CameraBoomPitch->GetComponentRotation( ).Pitch ) );

FRotator cuttentRotation = m_CameraBoomPitch->GetComponentRotation( );
   if( cuttentRotation.Pitch > 70.f )
      {
      
      m_CameraBoomPitch->SetWorldRotation( FRotator( 70.f, cuttentRotation.Yaw, cuttentRotation.Roll ) );
      }
   else if( m_CameraBoomPitch->GetComponentRotation( ).Pitch < -70.f )
      {
      m_CameraBoomPitch->SetWorldRotation( FRotator( -70.f, cuttentRotation.Yaw, cuttentRotation.Roll ) );
      }

}

//return ture if seting character and cameraboom sucess 
//else leave
bool AViewablePlayerController::SetControllingCharacter( APawn* InPawn )
{
   ABasicCharacter *character = Cast<ABasicCharacter>( InPawn );

   if( character )
      {
      m_ControllingCharacter = character;
      m_CameraBoomYaw = character->GetCameraBoomShift();
      m_CameraBoomPitch = character->GetCameraBoomRotation( );
      if( m_CameraBoomYaw && m_CameraBoomPitch )
         {
         return true;
         }
      
      }
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess cast fail" );
   return false;
}



