// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"


// Sets default values
ABasicCharacter::ABasicCharacter( const FObjectInitializer& ObjectInitializer )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   m_PitchRotUpperBound = 50.f;
   m_PitchRotLowerBound = -50.f;

   m_CameraScrollSpeed = 1000.f;
   m_CameraDisUpperBound = 700.f;
   m_CameraDisLowerBound = 100.f;


   m_ThirdPersonArmYaw = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For ThirdPerson Camera Spring Arm Yaw Rotation" ) );
   m_ThirdPersonArmYaw->AttachTo( RootComponent );
   m_ThirdPersonArmYaw->TargetArmLength = 75.0f;
   m_ThirdPersonArmYaw->bUsePawnControlRotation = false;

   m_ThirdPersonArmPitch = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For ThirdPerson Camera Spring Arm Pitch Rotation" ) );
   m_ThirdPersonArmPitch->AttachTo( m_ThirdPersonArmYaw );
   m_ThirdPersonArmPitch->TargetArmLength = 200.0f;
   m_ThirdPersonArmPitch->bUsePawnControlRotation = false;

   m_PlayerCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>( this, TEXT( "ThirdPerson Player Camera" ) );
   m_PlayerCamera->AttachTo( m_ThirdPersonArmPitch );
   m_PlayerCamera->Activate( );

   m_CurrentViewType = PlayerViewTypes::PlayerViewTypes_ThirdPerson;

}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasicCharacter::SetViewPointToThirdPerson( )
{
   m_PlayerCamera->AttachTo( m_ThirdPersonArmPitch );
   m_PlayerCamera->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
   m_CurrentViewType = PlayerViewTypes::PlayerViewTypes_ThirdPerson;
}

void ABasicCharacter::SetViewPointToFirstPerson( )
{
   FVector viewLocation;
   FRotator viewRotation;
   GetActorEyesViewPoint( viewLocation, viewRotation );
  // m_PlayerCamera->SetWorldLocation( viewLocation );
   m_PlayerCamera->AttachTo( RootComponent );
   m_PlayerCamera->SetWorldLocationAndRotation( viewLocation, viewRotation );
   
   m_CurrentViewType = PlayerViewTypes::PlayerViewTypes_FirstPerson;
   //m_PlayerCamera->Att
}

// Called every frame
void ABasicCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABasicCharacter::MoveForward( float amount )
{
   FVector fwd = GetActorForwardVector( );
   AddMovementInput( fwd, amount );
}

void ABasicCharacter::MoveRight( float amount )
{
   FVector right = GetActorRightVector( );
   AddMovementInput( right, amount );
}

void ABasicCharacter::SetCameraYaw( float amount )
{
   if( m_CurrentViewType == PlayerViewTypes::PlayerViewTypes_ThirdPerson )
      {
      m_ThirdPersonArmYaw->AddRelativeRotation( FRotator( 0, 200.f * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
      }
   else
      {
      AddControllerYawInput( 200.f * amount * GetWorld( )->GetDeltaSeconds( ) );
      }
}

void ABasicCharacter::SetCameraPitch( float amount )
{
   if( m_CurrentViewType == PlayerViewTypes::PlayerViewTypes_ThirdPerson )
      {
      m_ThirdPersonArmPitch->AddRelativeRotation( FRotator( 200.f * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
      FRotator currentRotation = m_ThirdPersonArmPitch->GetComponentRotation( );
      float clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, m_PitchRotLowerBound, m_PitchRotUpperBound );
      m_ThirdPersonArmPitch->SetWorldRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
      }
   else
      {
      m_PlayerCamera->AddRelativeRotation( FRotator( 200.f * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
      FTransform cuttrntTransform = m_PlayerCamera->GetRelativeTransform();
      FRotator currentRotation = cuttrntTransform.Rotator();
      float clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, m_PitchRotLowerBound, m_PitchRotUpperBound );
      m_PlayerCamera->SetRelativeRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
      }
}
void ABasicCharacter::SetCameraDistance( float amount )
{
   m_ThirdPersonArmPitch->TargetArmLength += m_CameraScrollSpeed * amount * -1.f * GetWorld( )->GetDeltaSeconds( );
   m_ThirdPersonArmPitch->TargetArmLength = FMath::Clamp<float>( m_ThirdPersonArmPitch->TargetArmLength, m_CameraDisLowerBound, m_CameraDisUpperBound );
}

void UpdateCameraLocationAndRotation( float DeltaSeconds )
 {
 }