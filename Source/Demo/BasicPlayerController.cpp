// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicPlayerController.h"
#include "BasicCharacter.h"

ABasicPlayerController::ABasicPlayerController( const FObjectInitializer& ObjectInitializer )
{
   PrimaryActorTick.bCanEverTick = true;

   m_Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>( this, TEXT( "Player Camera" ) );

}

void ABasicPlayerController::SetupInputComponent( )
{
   Super::SetupInputComponent( );
   InputComponent->BindAxis( "Forward", this, &ABasicPlayerController::MoveForward );
   InputComponent->BindAxis( "Strafe", this, &ABasicPlayerController::MoveRight );
   InputComponent->BindAxis( "Yaw", this, &ABasicPlayerController::Yaw );
   InputComponent->BindAxis( "Pitch", this, &ABasicPlayerController::Pitch );
}

void ABasicPlayerController::BeginPlay( )
{
   Super::BeginPlay( );
      SetControllingCharacter( Cast<ABasicCharacter>( GetPawn() ) );
   if( !m_ControllingCharacter )
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "error:null character pointer" );
}

void ABasicPlayerController::Possess( APawn * InPawn )
{
   if( SetControllingCharacter( InPawn ) )
      {
      Super::Possess( InPawn );
      m_Camera->AttachTo( m_ControllingCharacter->m_SpringArm );
      m_Camera->bUsePawnControlRotation = false;
      SetViewTarget( this );
   //   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess " );
      }
   else
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess failed" );
      }
}

void ABasicPlayerController::CalcCamera( float DeltaTime, struct FMinimalViewInfo& OutResult )
{
   m_Camera->GetCameraView( DeltaTime, OutResult );
}

void ABasicPlayerController::Tick( float DeltaTime )
{
   Super::Tick( DeltaTime );
}

void ABasicPlayerController::MoveForward( float amount )
{
   if( m_ControllingCharacter )
      {
      FVector fwd = m_ControllingCharacter->GetActorForwardVector( );
      m_ControllingCharacter->AddMovementInput( fwd, amount );
      }
}

void ABasicPlayerController::MoveRight( float amount )
{
   if( m_ControllingCharacter )
      {
      FVector right = m_ControllingCharacter->GetActorRightVector( );
      m_ControllingCharacter->AddMovementInput( right, amount );
      }
}

void ABasicPlayerController::Yaw( float amount )
{

   AddYawInput( 200.f * amount * GetWorld( )->GetDeltaSeconds( ) );

}

void ABasicPlayerController::Pitch( float amount )
{
   AddPitchInput( 200.f * amount * -1.f * GetWorld( )->GetDeltaSeconds( ) );
}
//return ture if set character sucess and set m_ControllingCharacter
//else leave
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

