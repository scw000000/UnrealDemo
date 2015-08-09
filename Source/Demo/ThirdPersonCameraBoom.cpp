// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "ThirdPersonCameraBoom.h"
#include "BasicCharacter.h"

AThirdPersonCameraBoom::AThirdPersonCameraBoom( const FObjectInitializer& ObjectInitializer )
{
//GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "BOOM spawned" );
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;
   m_CharacterCenter = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>( this, TEXT( "Root component of this camer boom" ) );
   RootComponent = m_CharacterCenter;

   m_CameraBoomYaw = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For Camera Spring Arm Yaw Rotation" ) );
   m_CameraBoomYaw->AttachTo( m_CharacterCenter );
   m_CameraBoomYaw->TargetArmLength = 75.0f;
   m_CameraBoomYaw->bUsePawnControlRotation = false;

   m_CameraBoomPitch = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For Camera Spring Arm Pitch Rotation" ) );
   m_CameraBoomPitch->AttachTo( m_CameraBoomYaw );
   m_CameraBoomPitch->TargetArmLength = 200.0f;
   m_CameraBoomPitch->bUsePawnControlRotation = false;
}

bool AThirdPersonCameraBoom::AttachToCharacter( ABasicCharacter *inCharacter )
{
   if( inCharacter )
      {
      RootComponent->SetAbsolute( true, true, true );
      SetActorLocationAndRotation( inCharacter->GetRootComponent( )->GetComponentLocation( ), inCharacter->GetRootComponent( )->GetComponentRotation( ) );
      AttachRootComponentToActor( inCharacter );
      return true;
      }
   else
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "err: camera boom null ptr error in ViewablePlayerController::AttachCameraComponents" );
      return false;
      }
}

void AThirdPersonCameraBoom::Yaw( float amount )
{
   m_CameraBoomYaw->AddRelativeRotation( FRotator( 0, 200.f * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
}

void AThirdPersonCameraBoom::Pitch( float amount )
{
   m_CameraBoomPitch->AddRelativeRotation( FRotator( 200.f * amount * -1.f * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
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

USceneComponent* AThirdPersonCameraBoom::GetCameraAttachComponent( )
{
   return m_CameraBoomPitch;
}

FName AThirdPersonCameraBoom::GetSocketName( )
{
   return m_CameraBoomPitch->SocketName;
}




