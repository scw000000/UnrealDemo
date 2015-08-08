// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "ThirdPersonCameraBoom.h"
#include "BasicCharacter.h"
#include "ViewablePlayerController.h"


AViewablePlayerController::AViewablePlayerController( const FObjectInitializer& ObjectInitializer )
{
   PrimaryActorTick.bCanEverTick = true;
   //DO NOT LET camera be rootcomponent in controller!!
   m_Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>( this, TEXT( "Player Camera" ) );
//   RootComponent = m_Camera;
  // m_Camera->AttachTo( RootComponent );
   //m_CameraBoom = GetWorld( )->SpawnActor< AThirdPersonCameraBoom >( m_BPCameraBoom );
  // m_CameraBoom = NULL;
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
   AttachToCameraBoom();
   //should set camera here!!
}

void AViewablePlayerController::CalcCamera( float DeltaTime, struct FMinimalViewInfo& OutResult )
{
   m_Camera->GetCameraView( DeltaTime, OutResult );
}

void AViewablePlayerController::AttachToCameraBoom( )
{
if( m_ControllingCharacter &&  m_ControllingCharacter->m_CameraBoom )
   {
   if( m_Camera )
      {
      ACameraBoom *cameraBoom = m_ControllingCharacter->m_CameraBoom;
      m_Camera->SetWorldLocationAndRotation( cameraBoom->GetCameraAttachComponent( )->GetSocketLocation( cameraBoom->GetSocketName( ) ), cameraBoom->GetActorRotation( ) );
      m_Camera->AttachTo( cameraBoom->GetCameraAttachComponent( ) );
      }
   else
      {
GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "camera null" );
      }
      
   }
else
GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "camera boom null" );
}

void AViewablePlayerController::Tick( float DeltaTime )
{
   Super::Tick( DeltaTime );
 //  AttachToCameraBoom();
}
//needs to disable "use pawn contorl rotation" in spring arm->camera settings
void AViewablePlayerController::Yaw( float amount )
{
if( m_ControllingCharacter && m_ControllingCharacter->m_CameraBoom )
      {
      m_ControllingCharacter->m_CameraBoom->Yaw( amount );
      }
      
//m_ControllingCharacter->m_SpringArm->Add
  // AddYawInput( 200.f * amount * GetWorld( )->GetDeltaSeconds( ) );
//m_CameraBoomYaw->AddRelativeRotation( FRotator( 0, 200.f * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );

}

void AViewablePlayerController::Pitch( float amount )
{
if( m_ControllingCharacter && m_ControllingCharacter->m_CameraBoom )
      {
      m_ControllingCharacter->m_CameraBoom->Pitch( amount );
      }
/*
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
   */
}

//return ture if seting character and cameraboom sucess 
//else leave




