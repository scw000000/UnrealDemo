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
}

void AViewablePlayerController::SetupInputComponent( )
{
   Super::SetupInputComponent( );
   InputComponent->BindAxis( "MouseX", this, &AViewablePlayerController::Yaw );
   InputComponent->BindAxis( "MouseY", this, &AViewablePlayerController::Pitch );

 //  InputComponent->BindAxis( "Forward", this, &AViewablePlayerController::MoveForward );
 //  InputComponent->BindAxis( "Strafe", this, &AViewablePlayerController::MoveRight );
}

void AViewablePlayerController::PostInitializeComponents( )
{
   Super::PostInitializeComponents( );
   m_CameraBoom = GetWorld( )->SpawnActor< AThirdPersonCameraBoom >( m_BPCameraBoom );
   if( !m_CameraBoom )
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "camera boom spawn failed" );
      }
}

void AViewablePlayerController::BeginPlay( )
{
   Super::BeginPlay( );
   
   //should set camera here!!
}

void AViewablePlayerController::CalcCamera( float DeltaTime, struct FMinimalViewInfo& OutResult )
{
   m_Camera->GetCameraView( DeltaTime, OutResult );
}

void AViewablePlayerController::AttachCameraComponents( )
{
   if( m_CameraBoom )
   {
   m_CameraBoom->GetRootComponent( )->AttachTo( m_ControllingCharacter->GetRootComponent() );
   FString Boomloacation = FString(" boom X: ") + FString::SanitizeFloat( m_CameraBoom->GetRootComponent( )->GetComponentLocation().X )
      + FString( " y: " ) + FString::SanitizeFloat( m_CameraBoom->GetRootComponent( )->GetComponentLocation( ).Y ) +
      FString( " Z: " ) + FString::SanitizeFloat( m_CameraBoom->GetRootComponent( )->GetComponentLocation( ).Z );

   FString Characterloacation = FString( " char X: " ) + FString::SanitizeFloat( m_ControllingCharacter->GetRootComponent( )->GetComponentLocation( ).X )
      + FString( " y: " ) + FString::SanitizeFloat( m_ControllingCharacter->GetRootComponent( )->GetComponentLocation( ).Y ) +
      FString( " Z: " ) + FString::SanitizeFloat( m_ControllingCharacter->GetRootComponent( )->GetComponentLocation( ).Z );
  // m_CameraBoom->AttachToCharacter( m_ControllingCharacter );
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, Characterloacation );
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, Boomloacation );
   }
   if( m_CameraBoom && m_Camera )
      {
     // m_Camera->SetAbsolute( true, true, true );

      m_CameraBoom->PrintText();

      m_Camera->SetWorldLocationAndRotation( m_CameraBoom->GetCameraAttachComponent( )->GetSocketLocation( m_CameraBoom->GetSocketName( ) ), m_CameraBoom->GetActorRotation( ) );
     // m_Camera->SetAbsolute( false, false, false );
      m_Camera->AttachTo( m_CameraBoom->GetCameraAttachComponent( ), m_CameraBoom->GetSocketName( ) );
      }
   else
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "err: amera boom or camer null ptr" );
      }
   FString Cameraloacation = FString( " Came X: " ) + FString::SanitizeFloat( m_Camera->GetComponentLocation( ).X )
      + FString( " y: " ) + FString::SanitizeFloat( m_Camera->GetComponentLocation( ).Y ) +
      FString( " Z: " ) + FString::SanitizeFloat( m_Camera->GetComponentLocation( ).Z );
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, Cameraloacation );
   FString Camerarevloacation = FString( " Came rev X: " ) + FString::SanitizeFloat( m_Camera->RelativeLocation.X )
      + FString( " y: " ) + FString::SanitizeFloat( m_Camera->RelativeLocation.Y ) +
      FString( " Z: " ) + FString::SanitizeFloat( m_Camera->RelativeLocation.Z );
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, Camerarevloacation );
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "---------------------------" );
}

void AViewablePlayerController::Tick( float DeltaSeconds )
{
   Super::Tick( DeltaSeconds );

   if( m_ControllingCharacter )
      {
      m_CameraBoom->SetActorLocationAndRotation( m_ControllingCharacter->GetRootComponent( )->GetComponentLocation( ), m_ControllingCharacter->GetRootComponent( )->GetComponentRotation( ) );
      }
}

void AViewablePlayerController::Possess( APawn * InPawn )
{
   Super::Possess( InPawn );
   SetViewTarget( this );
   AttachCameraComponents( );
}

//needs to disable "use pawn contorl rotation" in spring arm->camera settings
void AViewablePlayerController::Yaw( float amount )
{
   if( m_CameraBoom )
      {
      m_CameraBoom->Yaw( amount );
      }
}

void AViewablePlayerController::Pitch( float amount )
{
   if( m_CameraBoom )
      {
      m_CameraBoom->Pitch( amount );
      }
}

/*
void AViewablePlayerController::MoveForward( float amount )
{
   if( m_ControllingCharacter )
      {
      FVector fwd = m_ControllingCharacter->GetActorForwardVector( );
      m_ControllingCharacter->AddMovementInput( fwd, amount );
      }
}

void AViewablePlayerController::MoveRight( float amount )
{
   if( m_ControllingCharacter )
      {
      FVector right = m_ControllingCharacter->GetActorRightVector( );
      m_ControllingCharacter->AddMovementInput( right, amount );
      }
}
*/


