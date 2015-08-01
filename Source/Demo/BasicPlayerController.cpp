// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicPlayerController.h"
#include "BasicCharacter.h"

ABasicPlayerController::ABasicPlayerController( const FObjectInitializer& ObjectInitializer )
{
   PrimaryActorTick.bCanEverTick = true;
   
}

void ABasicPlayerController::BeginPlay( )
{
   Super::BeginPlay( );
      SetControllingCharacter( Cast<ABasicCharacter>( GetPawn() ) );
   if( !m_ControllingCharacter )
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "error:null character pointer" );
}

void ABasicPlayerController::SetupInputComponent( )
{
   Super::SetupInputComponent( );
   InputComponent->BindAxis( "Forward", this, &ABasicPlayerController::MoveForward );
   InputComponent->BindAxis( "Strafe", this, &ABasicPlayerController::MoveRight );
   InputComponent->BindAxis( "Yaw", this, &ABasicPlayerController::Yaw );
   InputComponent->BindAxis( "Pitch", this, &ABasicPlayerController::Pitch );
}

void ABasicPlayerController::Tick( float DeltaTime )
{
   Super::Tick( DeltaTime );
}

void ABasicPlayerController::MoveForward( float amount )
{
   FVector fwd = m_ControllingCharacter->GetActorForwardVector( );
   m_ControllingCharacter->AddMovementInput( fwd, amount );
      
}

void ABasicPlayerController::MoveRight( float amount )
{
   FVector right = m_ControllingCharacter->GetActorRightVector( );
   m_ControllingCharacter->AddMovementInput( right, amount );
}

void ABasicPlayerController::Yaw( float amount )
{

   AddYawInput( 200.f * amount * GetWorld( )->GetDeltaSeconds( ) );

}

void ABasicPlayerController::Pitch( float amount )
{
   AddPitchInput( 200.f * amount * -1.f * GetWorld( )->GetDeltaSeconds( ) );
}

void ABasicPlayerController::SetControllingCharacter( ABasicCharacter* character )
{
   m_ControllingCharacter = character;
}

