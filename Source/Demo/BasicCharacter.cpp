// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"


// Sets default values
ABasicCharacter::ABasicCharacter( const FObjectInitializer& ObjectInitializer )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   maxCameraPitch = 50.f;
   minCameraPitch = -50.f;
   cameraScrollSpeed = 1000.f;
   cameraRotateSpeed = 100.f;
   maxCameraDistance = 700.f;
   minCameraDistance = 100.f;

   idleTime = 0.f;

   bUseControllerRotationPitch = false;
   bUseControllerRotationYaw = false;
   bUseControllerRotationRoll = false;

   GetCharacterMovement( )->bOrientRotationToMovement = true;

   thirdPersonCameraBoomYaw = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For ThirdPerson Camera Spring Arm Yaw Rotation" ) );
   thirdPersonCameraBoomYaw->AttachTo( RootComponent );
   thirdPersonCameraBoomYaw->TargetArmLength = 75.0f;
   thirdPersonCameraBoomYaw->bUsePawnControlRotation = false;
   thirdPersonCameraBoomYaw->SetAbsolute( false, true, false );

   thirdPersonCameraBoomPitch = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For ThirdPerson Camera Spring Arm Pitch Rotation" ) );
   thirdPersonCameraBoomPitch->AttachTo( thirdPersonCameraBoomYaw );
   thirdPersonCameraBoomPitch->TargetArmLength = 150.0f;
   thirdPersonCameraBoomPitch->bUsePawnControlRotation = false;

   playerCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>( this, TEXT( "ThirdPerson Player Camera" ) );
   playerCamera->AttachTo( thirdPersonCameraBoomPitch );
   playerCamera->Activate( );

   aimingCameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For Aiming location setting" ) );
   aimingCameraBoom->TargetArmLength = 50.0f;
   aimingCameraBoom->AttachTo( RootComponent );

   playerView = PlayerViews::PlayerViews_ThirdPerson;
   armMotion = ArmMotions::ArmMotions_Default;
   bodyMotion = BodyMotions::BodyMotions_Idle;
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABasicCharacter::Jump( )
{
   WakePlayer();
   if( bodyMotion == BodyMotions::BodyMotions_Jog || bodyMotion == BodyMotions::BodyMotions_Idle )
      {
      Super::Jump();
      bodyMotion = ( bodyMotion == BodyMotions::BodyMotions_Jog )?
            bodyMotion = BodyMotions::BodyMotions_JogJump:
            bodyMotion = BodyMotions::BodyMotions_Jump;
      }
}

void ABasicCharacter::ToggleProne()
{
   
}

void ABasicCharacter::StartAttack()
{
   if( playerView == PlayerViews::PlayerViews_Aim )
      {
      armMotion = ArmMotions::ArmMotions_IronSightFire;
      }
   else
      {
      armMotion = ArmMotions::ArmMotions_DefaultFire;
      }
}

void ABasicCharacter::StopAttack()
{
   if( playerView == PlayerViews::PlayerViews_Aim )
      {
      armMotion = ArmMotions::ArmMotions_IronSight;
      }
   else
      {
      armMotion = ArmMotions::ArmMotions_Default;
      }
}

// Called every frame
void ABasicCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
   RefineMotionType( DeltaTime );
}
/**
This may be useful:
https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/ACharacter/OnStartCrouch/index.html
https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/ACharacter/OnStartCrouch/index.html
*/
void ABasicCharacter::Crouch( bool bClientSimulation)
{
      
   //   aimingCameraBoom->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 70.f - BaseEyeHeight + CrouchedEyeHeight ) );
      if( bodyMotion == BodyMotions::BodyMotions_Jog || bodyMotion == BodyMotions::BodyMotions_Idle )
         {     
         Super::Crouch( bClientSimulation );
         WakePlayer();
         FVector aimArmRelativeLocation = aimingCameraBoom->GetRelativeTransform( ).GetLocation();
         aimingCameraBoom->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 5.f ) );

         bodyMotion = ( bodyMotion == BodyMotions::BodyMotions_Jog )?
            bodyMotion = BodyMotions::BodyMotions_CrouchJog:
            bodyMotion = BodyMotions::BodyMotions_CrouchIdle;
         }
}

void ABasicCharacter::UnCrouch( bool bClientSimulation )
{
   if( bodyMotion == BodyMotions::BodyMotions_CrouchJog || bodyMotion == BodyMotions::BodyMotions_CrouchIdle)
      {
      Super::UnCrouch( bClientSimulation );
      WakePlayer();
      FVector aimArmRelativeLocation = aimingCameraBoom->GetRelativeTransform( ).GetLocation( );
      aimingCameraBoom->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 70.f ) );

      bodyMotion = ( bodyMotion == BodyMotions::BodyMotions_CrouchJog )?
            bodyMotion = BodyMotions::BodyMotions_Jog:
            bodyMotion = BodyMotions::BodyMotions_Idle;
      }
}

void ABasicCharacter::SetPlayerView( PlayerViews inViewType )
{
   switch( inViewType )
      {
         case PlayerViews::PlayerViews_ThirdPerson:
            SetPlayerViewToThirdPerson( );
            break;
      case PlayerViews::PlayerViews_Aim:
            SetPlayerViewToAim( );
            break;
      case PlayerViews::PlayerViews_FirstPerson:
            SetPlayerViewToFirstPerson( );
            break;
      //default:
      }
}

void ABasicCharacter::MoveForward( float amount )
{
   WakePlayer();
   FVector fwd = playerCamera->GetForwardVector();
   AddMovementInput( fwd, amount, false );
}

void ABasicCharacter::MoveRight( float amount )
{
   WakePlayer();
   FVector right = playerCamera->GetRightVector();
   AddMovementInput( right, amount, false );
}

void ABasicCharacter::SetCamYaw( const float& amount )
{
   switch( playerView )
      {
         case PlayerViews::PlayerViews_ThirdPerson :
            thirdPersonCameraBoomYaw->AddRelativeRotation( FRotator( 0, cameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
            break;
         case PlayerViews::PlayerViews_Aim:
      //      AddActorWorldRotation( FRotator( 0, cameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
    //        break;
         case PlayerViews::PlayerViews_FirstPerson :
            AddActorWorldRotation( FRotator( 0, cameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
            break;
       //  default:
      }
}

void ABasicCharacter::SetCamPitch( const float& amount )
{
   float clampedPitch;
   FRotator currentRotation;
   FTransform cuttrntTransform;
   switch( playerView )
      {
      case PlayerViews::PlayerViews_ThirdPerson :
         thirdPersonCameraBoomPitch->AddRelativeRotation( FRotator( cameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
         currentRotation = thirdPersonCameraBoomPitch->GetComponentRotation( );
         clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, minCameraPitch, maxCameraPitch );
         thirdPersonCameraBoomPitch->SetWorldRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
         break;
      case PlayerViews::PlayerViews_Aim:
        /// playerCamera->AddRelativeRotation( FRotator( cameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
     //    cuttrntTransform = playerCamera->GetRelativeTransform( );
       //  currentRotation = cuttrntTransform.Rotator( );
      //   clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, minCameraPitch, maxCameraPitch );
      //   playerCamera->SetRelativeRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
      //   break;
      case PlayerViews::PlayerViews_FirstPerson:
         playerCamera->AddRelativeRotation( FRotator( cameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
         cuttrntTransform = playerCamera->GetRelativeTransform( );
         currentRotation = cuttrntTransform.Rotator( );
         clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, minCameraPitch, maxCameraPitch );
         playerCamera->SetRelativeRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
         break;
  //    default:
      }
}
void ABasicCharacter::SetCamDistance( const float& amount )
{
   thirdPersonCameraBoomPitch->TargetArmLength += cameraScrollSpeed * amount * -1.f * GetWorld( )->GetDeltaSeconds( );
   thirdPersonCameraBoomPitch->TargetArmLength = FMath::Clamp<float>( thirdPersonCameraBoomPitch->TargetArmLength, minCameraDistance, maxCameraDistance );
}

//reset idle time and set its bodymotion
void ABasicCharacter::WakePlayer()
{
   idleTime = 0.f;
   if( bodyMotion == BodyMotions::BodyMotions_Break )
      {
      bodyMotion = BodyMotions::BodyMotions_Idle;
      }
}

void ABasicCharacter::AddIdleTime( const float& inTime )
{
   idleTime += inTime;
}

void ABasicCharacter::RefineMotionType( const float& DeltaSeconds )
{
   switch( bodyMotion )
      {
         case BodyMotions::BodyMotions_Idle:
         case BodyMotions::BodyMotions_Jog:
            RefineMotionStand( DeltaSeconds );
            break;
         case BodyMotions::BodyMotions_CrouchIdle:
         case BodyMotions::BodyMotions_CrouchJog:
            RefineMotionCrouch();
            break;
         case BodyMotions::BodyMotions_Fall:
            RefineMotionFall();
            break;
         case BodyMotions::BodyMotions_Jump:
            RefineMotionJump();
            break;
         case BodyMotions::BodyMotions_JogJump:
            RefineMotionJogJump();
            break;
         case BodyMotions::BodyMotions_Break:
            break;
      }

}

void ABasicCharacter::RefineMotionStand( const float& DeltaSeconds )
{
   //if NOT falling(stay on ground)
   if( !GetMovementComponent( )->IsFalling( ) )
      {
      if( GetVelocity( ).Size( ) > 5.f )//On ground and moving
         {
         bodyMotion = BodyMotions::BodyMotions_Jog;
         }
      else //On ground and barely not moving
         {
         bodyMotion = BodyMotions::BodyMotions_Idle;
         if( armMotion == ArmMotions::ArmMotions_Default )//player is not busying using weapon
            {
            idleTime += DeltaSeconds;
            if( idleTime >= 12.6f )
               {
               bodyMotion = BodyMotions::BodyMotions_Break;
               }
            }
         }
      }
   else //is falling
      {
      bodyMotion = BodyMotions::BodyMotions_Fall;
      }
}

void ABasicCharacter::RefineMotionCrouch( )
{
   if( !GetMovementComponent( )->IsFalling( ) )//Is NOT falling
      {
      if( GetVelocity( ).Size( ) <= 5.f )//On ground and barely not moving
         {
         bodyMotion = BodyMotions::BodyMotions_CrouchIdle;
         }
      else
         {
         bodyMotion = BodyMotions::BodyMotions_CrouchJog;
         }
      }
   else //is falling
      {
       bodyMotion = BodyMotions::BodyMotions_Fall;
      }
 
}

void ABasicCharacter::RefineMotionFall()
{
   if( !GetMovementComponent( )->IsFalling( ) )//Is NOT falling
      {
         if( GetVelocity( ).Size( ) <= 5.f )//On ground and barely not moving
            {
            bodyMotion = BodyMotions::BodyMotions_Idle;
            }
         else
            {
            bodyMotion = BodyMotions::BodyMotions_Jog;
           }
      }
}

void ABasicCharacter::RefineMotionJump( )
{
   //if NOT falling(stay on ground)
   if( !GetMovementComponent( )->IsFalling( ) )
      {
      bodyMotion = BodyMotions::BodyMotions_Idle;
      }
}

void ABasicCharacter::RefineMotionJogJump( )
{
   //if NOT falling(stay on ground)
   if( !GetMovementComponent( )->IsFalling( ) )
   {
   bodyMotion = BodyMotions::BodyMotions_Jog;
   }
}

void ABasicCharacter::RefineMotionBreak( )
{
   if( GetVelocity( ).Size( ) > 5.f )
    {
    bodyMotion = BodyMotions::BodyMotions_Idle;
    }
}

void ABasicCharacter::SetPlayerViewToThirdPerson( )
{
   GetCharacterMovement( )->bOrientRotationToMovement = true;
   GetMesh( )->SetVisibility( true );
   playerCamera->AttachTo( thirdPersonCameraBoomPitch );
   FRotator currentActorRotation = GetActorRotation( );
   thirdPersonCameraBoomYaw->SetWorldRotation( FRotator( currentActorRotation.Pitch, currentActorRotation.Yaw, currentActorRotation.Roll ) );
   playerCamera->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
   playerView = PlayerViews::PlayerViews_ThirdPerson;
   armMotion = ArmMotions::ArmMotions_Default;
}

void ABasicCharacter::SetPlayerViewToAim( )
{
   GetCharacterMovement( )->bOrientRotationToMovement = false;
   GetMesh( )->SetVisibility( true );
   aimingCameraBoom->SetRelativeRotation( FRotator::ZeroRotator );
   SetActorRotation( FRotator( GetActorRotation( ).Pitch, playerCamera->GetComponentRotation( ).Yaw, GetActorRotation( ).Roll ) );
   playerCamera->AttachTo( aimingCameraBoom );
   playerCamera->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
   playerView = PlayerViews::PlayerViews_Aim;
   armMotion = ArmMotions::ArmMotions_IronSight;
}

void ABasicCharacter::SetPlayerViewToFirstPerson( )
{
   FVector viewLocation;
   FRotator viewRotation;
   GetCharacterMovement( )->bOrientRotationToMovement = false;
   GetMesh( )->SetVisibility( false );
   SetActorRotation( FRotator( GetActorRotation( ).Pitch, playerCamera->GetComponentRotation( ).Yaw, GetActorRotation( ).Roll ) );
   GetActorEyesViewPoint( viewLocation, viewRotation );
   playerCamera->AttachTo( RootComponent );
   playerCamera->SetWorldLocation( viewLocation );
   playerCamera->SetRelativeRotation( FRotator::ZeroRotator );
   //playerCamera->SetWorldLocationAndRotation( viewLocation, viewRotation );
   armMotion = ArmMotions::ArmMotions_IronSight;
   playerView = PlayerViews::PlayerViews_FirstPerson;
   //playerCamera->Att
}

void UpdateCameraLocationAndRotation( const float& DeltaSeconds )
 {
 }