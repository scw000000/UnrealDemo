// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"
#include "SingleArmCameraBoom.h"


ASingleArmCameraBoom::ASingleArmCameraBoom( const FObjectInitializer& ObjectInitializer )
   {
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;
   m_CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For Camera Spring Arm Yaw Rotation" ) );
   RootComponent = m_CameraBoom;
   m_CameraBoom->TargetArmLength = 300.0f;
   m_CameraBoom->bUsePawnControlRotation = false;

   }

bool ASingleArmCameraBoom::AttachToCharacter( ABasicCharacter *inCharacter )
   {
   if( inCharacter )
      {

      m_CameraBoom->AttachTo( inCharacter->GetRootComponent( ) );
      return true;
      }
   else
      {
      return false;
      }

   }

void ASingleArmCameraBoom::Yaw( float amount )
   {
   m_CameraBoom->AddRelativeRotation( FRotator( 0, 200.f * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
   }

void ASingleArmCameraBoom::Pitch( float amount )
   {
   m_CameraBoom->AddRelativeRotation( FRotator( 200.f * amount * -1.f * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
  // GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::SanitizeFloat( m_CameraBoom->GetComponentRotation( ).Pitch ) );

   FRotator cuttentRotation = m_CameraBoom->GetComponentRotation( );
   if( cuttentRotation.Pitch > 70.f )
      {

      m_CameraBoom->SetWorldRotation( FRotator( 70.f, cuttentRotation.Yaw, cuttentRotation.Roll ) );
      }
   else if( m_CameraBoom->GetComponentRotation( ).Pitch < -70.f )
      {
      m_CameraBoom->SetWorldRotation( FRotator( -70.f, cuttentRotation.Yaw, cuttentRotation.Roll ) );
      }
   }

USceneComponent* ASingleArmCameraBoom::GetCameraAttachComponent( )
   {
   return m_CameraBoom;
   }


