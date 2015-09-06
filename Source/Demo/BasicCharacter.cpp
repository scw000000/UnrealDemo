// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"


// Sets default values
ABasicCharacter::ABasicCharacter( const FObjectInitializer& ObjectInitializer )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   camPitchMax = 50.f;
   camPitchMin = -50.f;
   camScrollSpeed = 1000.f;
   camRotSpeed = 100.f;
   camDistanceMax = 700.f;
   camDistanceMin = 100.f;

   idleTime = 0.f;

   bUseControllerRotationPitch = false;
   bUseControllerRotationYaw = false;
   bUseControllerRotationRoll = false;

   GetCharacterMovement( )->bOrientRotationToMovement = true;

   thirdPersonCamBoomYaw = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For ThirdPerson Camera Spring Arm Yaw Rotation" ) );
   thirdPersonCamBoomYaw->AttachTo( RootComponent );
   thirdPersonCamBoomYaw->TargetArmLength = 75.0f;
   thirdPersonCamBoomYaw->bUsePawnControlRotation = false;
   thirdPersonCamBoomYaw->SetAbsolute( false, true, false );

   thirdPersonCamBoomPitch = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For ThirdPerson Camera Spring Arm Pitch Rotation" ) );
   thirdPersonCamBoomPitch->AttachTo( thirdPersonCamBoomYaw );
   thirdPersonCamBoomPitch->TargetArmLength = 150.0f;
   thirdPersonCamBoomPitch->bUsePawnControlRotation = false;

   playerCam = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>( this, TEXT( "ThirdPerson Player Camera" ) );
   playerCam->AttachTo( thirdPersonCamBoomPitch );
   playerCam->Activate( );

   aimingCamBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "For Aiming location setting" ) );
   aimingCamBoom->TargetArmLength = 50.0f;
   aimingCamBoom->AttachTo( RootComponent );
   //aimingCamBoom->AttachTo( GetMesh(), GetMesh()->GetSocketBoneName("Socket_ViewPoint") );
   //aimingCamBoom->CanAttachAsChild
   //GetMesh()->GetSocketBoneName
    //  GetMesh()->GetSOcket
//   const USkeletalMeshSocket *socket = GetMesh( )->GetSocketByName("Socket_ViewPoint");
 //  socket->AttachActor( aimingCamBoom );
   //Socket_ViewPoint
   playerView = PlayerViews::PlayerViews_ThirdPerson;
   armMotion = ArmMotions::ArmMotions_Default;
   bodyMotion = BodyMotions::BodyMotions_Idle;

   m_Speed = 0.f;
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
   SetActorRotation( FRotator::ZeroRotator );
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

void ABasicCharacter::EndAttack()
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
      
   //   aimingCamBoom->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 70.f - BaseEyeHeight + CrouchedEyeHeight ) );
      if( bodyMotion == BodyMotions::BodyMotions_Jog || bodyMotion == BodyMotions::BodyMotions_Idle )
         {     
         Super::Crouch( bClientSimulation );
         WakePlayer();
         FVector aimArmRelativeLocation = aimingCamBoom->GetRelativeTransform( ).GetLocation();
         aimingCamBoom->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 5.f ) );

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
      FVector aimArmRelativeLocation = aimingCamBoom->GetRelativeTransform( ).GetLocation( );
      aimingCamBoom->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 70.f ) );

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
   FVector fwd = playerCam->GetForwardVector();
   AddMovementInput( fwd, amount, false );
}

void ABasicCharacter::MoveRight( float amount )
{
   WakePlayer();
   FVector right = playerCam->GetRightVector();
   AddMovementInput( right, amount, false );
}

void ABasicCharacter::SetCamYaw( float amount )
{
   switch( playerView )
      {
         case PlayerViews::PlayerViews_ThirdPerson :
            thirdPersonCamBoomYaw->AddRelativeRotation( FRotator( 0, camRotSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
            break;
         case PlayerViews::PlayerViews_Aim:
      //      AddActorWorldRotation( FRotator( 0, camRotSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
    //        break;
         case PlayerViews::PlayerViews_FirstPerson :
            AddActorWorldRotation( FRotator( 0, camRotSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
            break;
       //  default:
      }
}

void ABasicCharacter::SetCamPitch( float amount )
{
   float clampedPitch;
   FRotator currentRotation;
   FTransform cuttrntTransform;
   switch( playerView )
      {
      case PlayerViews::PlayerViews_ThirdPerson :
         thirdPersonCamBoomPitch->AddRelativeRotation( FRotator( camRotSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
         currentRotation = thirdPersonCamBoomPitch->GetComponentRotation( );
         clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, camPitchMin, camPitchMax );
         thirdPersonCamBoomPitch->SetWorldRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
         break;
      case PlayerViews::PlayerViews_Aim:
        /// playerCam->AddRelativeRotation( FRotator( camRotSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
     //    cuttrntTransform = playerCam->GetRelativeTransform( );
       //  currentRotation = cuttrntTransform.Rotator( );
      //   clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, camPitchMin, camPitchMax );
      //   playerCam->SetRelativeRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
      //   break;
      case PlayerViews::PlayerViews_FirstPerson:
         playerCam->AddRelativeRotation( FRotator( camRotSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
         cuttrntTransform = playerCam->GetRelativeTransform( );
         currentRotation = cuttrntTransform.Rotator( );
         clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, camPitchMin, camPitchMax );
         playerCam->SetRelativeRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
         break;
  //    default:
      }
}
void ABasicCharacter::SetCamDistance( float amount )
{
   thirdPersonCamBoomPitch->TargetArmLength += camScrollSpeed * amount * -1.f * GetWorld( )->GetDeltaSeconds( );
   thirdPersonCamBoomPitch->TargetArmLength = FMath::Clamp<float>( thirdPersonCamBoomPitch->TargetArmLength, camDistanceMin, camDistanceMax );
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

void ABasicCharacter::AddIdleTime( float inTime )
{
   idleTime += inTime;
}

void ABasicCharacter::RefineMotionType( float DeltaSeconds )
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

void ABasicCharacter::RefineMotionStand( float DeltaSeconds )
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
   playerCam->AttachTo( thirdPersonCamBoomPitch );
   FRotator currentActorRotation = GetActorRotation( );
   thirdPersonCamBoomYaw->SetWorldRotation( FRotator( currentActorRotation.Pitch, currentActorRotation.Yaw, currentActorRotation.Roll ) );
   playerCam->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
   playerView = PlayerViews::PlayerViews_ThirdPerson;
   armMotion = ArmMotions::ArmMotions_Default;
}

void ABasicCharacter::SetPlayerViewToAim( )
{
   GetCharacterMovement( )->bOrientRotationToMovement = false;
   GetMesh( )->SetVisibility( true );
   aimingCamBoom->SetRelativeRotation( FRotator::ZeroRotator );
   SetActorRotation( FRotator( GetActorRotation( ).Pitch, playerCam->GetComponentRotation( ).Yaw, GetActorRotation( ).Roll ) );
   playerCam->AttachTo( aimingCamBoom );
   playerCam->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
   playerView = PlayerViews::PlayerViews_Aim;
   armMotion = ArmMotions::ArmMotions_IronSight;
}

void ABasicCharacter::SetPlayerViewToFirstPerson( )
{
   FVector viewLocation;
   FRotator viewRotation;
   GetCharacterMovement( )->bOrientRotationToMovement = false;
   GetMesh( )->SetVisibility( false );
   SetActorRotation( FRotator( GetActorRotation( ).Pitch, playerCam->GetComponentRotation( ).Yaw, GetActorRotation( ).Roll ) );
   GetActorEyesViewPoint( viewLocation, viewRotation );
   playerCam->AttachTo( RootComponent );
   playerCam->SetWorldLocation( viewLocation );
   playerCam->SetRelativeRotation( FRotator::ZeroRotator );
   //playerCam->SetWorldLocationAndRotation( viewLocation, viewRotation );
   armMotion = ArmMotions::ArmMotions_IronSight;
   playerView = PlayerViews::PlayerViews_FirstPerson;
   //playerCam->Att
}

void UpdateCameraLocationAndRotation( float DeltaSeconds )
 {
 }