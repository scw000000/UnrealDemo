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

   m_CameraRotateSpeed = 100.f;

   m_CameraDisUpperBound = 700.f;
   m_CameraDisLowerBound = 100.f;

   bUseControllerRotationPitch = false;
   bUseControllerRotationYaw = false;
   bUseControllerRotationRoll = false;

   GetCharacterMovement( )->bOrientRotationToMovement = true;

   m_ThirdPersonArmYaw = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For ThirdPerson Camera Spring Arm Yaw Rotation" ) );
   m_ThirdPersonArmYaw->AttachTo( RootComponent );
   m_ThirdPersonArmYaw->TargetArmLength = 75.0f;
   m_ThirdPersonArmYaw->bUsePawnControlRotation = false;
   m_ThirdPersonArmYaw->SetAbsolute( false, true, false );

   m_ThirdPersonArmPitch = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For ThirdPerson Camera Spring Arm Pitch Rotation" ) );
   m_ThirdPersonArmPitch->AttachTo( m_ThirdPersonArmYaw );
   m_ThirdPersonArmPitch->TargetArmLength = 150.0f;
   m_ThirdPersonArmPitch->bUsePawnControlRotation = false;

   m_PlayerCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>( this, TEXT( "ThirdPerson Player Camera" ) );
   m_PlayerCamera->AttachTo( m_ThirdPersonArmPitch );
   m_PlayerCamera->Activate( );

   m_AimingArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For Aiming location setting" ) );
   m_AimingArm->TargetArmLength = 50.0f;
   m_AimingArm->AttachTo( RootComponent );


   m_CurrentViewType = PlayerViewTypes::PlayerViewTypes_ThirdPerson;

}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
   SetActorRotation( FRotator::ZeroRotator );
}

// Called every frame
void ABasicCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ABasicCharacter::SetViewType( PlayerViewTypes inViewType )
{
   switch( inViewType )
      {
         case PlayerViewTypes::PlayerViewTypes_ThirdPerson:
         SetViewTypeToThirdPerson( );
         break;
         case PlayerViewTypes::PlayerViewTypes_Aim:
         SetViewTypeToAim( );
         break;
         case PlayerViewTypes::PlayerViewTypes_FirstPerson:
         SetViewTypeToFirstPerson( );
         break;
         //    default:
      }
}


void ABasicCharacter::MoveForward( float amount )
{
   FVector fwd = m_PlayerCamera->GetForwardVector();
   AddMovementInput( fwd, amount );
}

void ABasicCharacter::MoveRight( float amount )
{
   FVector right = m_PlayerCamera->GetRightVector();
   AddMovementInput( right, amount );
}

void ABasicCharacter::SetCameraYaw( float amount )
{
   switch( m_CurrentViewType )
      {
         case PlayerViewTypes::PlayerViewTypes_ThirdPerson :
            m_ThirdPersonArmYaw->AddRelativeRotation( FRotator( 0, m_CameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
            break;
         case PlayerViewTypes::PlayerViewTypes_Aim :
            AddActorWorldRotation( FRotator( 0, m_CameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
            break;
         case PlayerViewTypes::PlayerViewTypes_FirstPerson :
            AddActorWorldRotation( FRotator( 0, m_CameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
            break;
       //  default:
      }
}

void ABasicCharacter::SetCameraPitch( float amount )
{
   float clampedPitch;
   FRotator currentRotation;
   FTransform cuttrntTransform;
   switch( m_CurrentViewType )
      {
      case PlayerViewTypes::PlayerViewTypes_ThirdPerson :
         m_ThirdPersonArmPitch->AddRelativeRotation( FRotator( m_CameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
         currentRotation = m_ThirdPersonArmPitch->GetComponentRotation( );
         clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, m_PitchRotLowerBound, m_PitchRotUpperBound );
         m_ThirdPersonArmPitch->SetWorldRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
         break;
      case PlayerViewTypes::PlayerViewTypes_Aim :
         m_PlayerCamera->AddRelativeRotation( FRotator( m_CameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
         cuttrntTransform = m_PlayerCamera->GetRelativeTransform( );
         currentRotation = cuttrntTransform.Rotator( );
         clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, m_PitchRotLowerBound, m_PitchRotUpperBound );
         m_PlayerCamera->SetRelativeRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
         break;
      case PlayerViewTypes::PlayerViewTypes_FirstPerson:
         m_PlayerCamera->AddRelativeRotation( FRotator( m_CameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
         cuttrntTransform = m_PlayerCamera->GetRelativeTransform( );
         currentRotation = cuttrntTransform.Rotator( );
         clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, m_PitchRotLowerBound, m_PitchRotUpperBound );
         m_PlayerCamera->SetRelativeRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
         break;
  //    default:
      }
}
void ABasicCharacter::SetCameraDistance( float amount )
{
   m_ThirdPersonArmPitch->TargetArmLength += m_CameraScrollSpeed * amount * -1.f * GetWorld( )->GetDeltaSeconds( );
   m_ThirdPersonArmPitch->TargetArmLength = FMath::Clamp<float>( m_ThirdPersonArmPitch->TargetArmLength, m_CameraDisLowerBound, m_CameraDisUpperBound );
}

void ABasicCharacter::SetViewTypeToThirdPerson( )
{
   GetCharacterMovement( )->bOrientRotationToMovement = true;
   GetMesh( )->SetVisibility( true );
   m_PlayerCamera->AttachTo( m_ThirdPersonArmPitch );
   FRotator currentActorRotation = GetActorRotation( );
   m_ThirdPersonArmYaw->SetWorldRotation( FRotator( currentActorRotation.Pitch, currentActorRotation.Yaw, currentActorRotation.Roll ) );
   m_PlayerCamera->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
   m_CurrentViewType = PlayerViewTypes::PlayerViewTypes_ThirdPerson;
}

void ABasicCharacter::SetViewTypeToAim( )
{
   GetCharacterMovement( )->bOrientRotationToMovement = false;
   GetMesh( )->SetVisibility( true );
   m_AimingArm->SetRelativeRotation( FRotator::ZeroRotator );
   SetActorRotation( FRotator( GetActorRotation( ).Pitch, m_PlayerCamera->GetComponentRotation( ).Yaw, GetActorRotation( ).Roll ) );
   m_PlayerCamera->AttachTo( m_AimingArm );
   m_PlayerCamera->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
   m_CurrentViewType = PlayerViewTypes::PlayerViewTypes_Aim;
}

void ABasicCharacter::SetViewTypeToFirstPerson( )
{
   FVector viewLocation;
   FRotator viewRotation;
   GetCharacterMovement( )->bOrientRotationToMovement = false;
   GetMesh( )->SetVisibility( false );
   SetActorRotation( FRotator( GetActorRotation( ).Pitch, m_PlayerCamera->GetComponentRotation( ).Yaw, GetActorRotation( ).Roll ) );
   GetActorEyesViewPoint( viewLocation, viewRotation );
   m_PlayerCamera->AttachTo( RootComponent );
   m_PlayerCamera->SetWorldLocation( viewLocation );
   m_PlayerCamera->SetRelativeRotation( FRotator::ZeroRotator );
   //m_PlayerCamera->SetWorldLocationAndRotation( viewLocation, viewRotation );

   m_CurrentViewType = PlayerViewTypes::PlayerViewTypes_FirstPerson;
   //m_PlayerCamera->Att
}

void UpdateCameraLocationAndRotation( float DeltaSeconds )
 {
 }