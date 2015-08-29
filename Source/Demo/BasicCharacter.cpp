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

   m_IdleTime = 0.f;

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
   //m_AimingArm->AttachTo( GetMesh(), GetMesh()->GetSocketBoneName("Socket_ViewPoint") );
   //m_AimingArm->CanAttachAsChild
   //GetMesh()->GetSocketBoneName
    //  GetMesh()->GetSOcket
//   const USkeletalMeshSocket *socket = GetMesh( )->GetSocketByName("Socket_ViewPoint");
 //  socket->AttachActor( m_AimingArm );
   //Socket_ViewPoint
   m_PlayerView = PlayerViews::PlayerViews_ThirdPerson;
   m_ArmMotion = ArmMotions::ArmMotions_Default;
   m_BodyMotion = BodyMotions::BodyMotions_Idle;
   m_EquippedWeapon = WeaponCategories::WeaponCategories_BareHand;
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
   if( m_BodyMotion == BodyMotions::BodyMotions_Jog || m_BodyMotion == BodyMotions::BodyMotions_Idle )
      {
      Super::Jump();
      m_BodyMotion = ( m_BodyMotion == BodyMotions::BodyMotions_Jog )?
            m_BodyMotion = BodyMotions::BodyMotions_JogJump:
            m_BodyMotion = BodyMotions::BodyMotions_Jump;
      }
}

void ABasicCharacter::StartAttack()
{
   if( m_PlayerView == PlayerViews::PlayerViews_Aim )
      {
      m_ArmMotion = ArmMotions::ArmMotions_IronSightFire;
      }
   else
      {
      m_ArmMotion = ArmMotions::ArmMotions_DefaultFire;
      }
}

void ABasicCharacter::EndAttack()
{
   if( m_PlayerView == PlayerViews::PlayerViews_Aim )
      {
      m_ArmMotion = ArmMotions::ArmMotions_IronSight;
      }
   else
      {
      m_ArmMotion = ArmMotions::ArmMotions_Default;
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
      
   //   m_AimingArm->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 70.f - BaseEyeHeight + CrouchedEyeHeight ) );
      if( m_BodyMotion == BodyMotions::BodyMotions_Jog || m_BodyMotion == BodyMotions::BodyMotions_Idle )
         {     
         Super::Crouch( bClientSimulation );
         WakePlayer();
         FVector aimArmRelativeLocation = m_AimingArm->GetRelativeTransform( ).GetLocation();
         m_AimingArm->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 5.f ) );

         m_BodyMotion = ( m_BodyMotion == BodyMotions::BodyMotions_Jog )?
            m_BodyMotion = BodyMotions::BodyMotions_CrouchJog:
            m_BodyMotion = BodyMotions::BodyMotions_CrouchIdle;
         }
}

void ABasicCharacter::UnCrouch( bool bClientSimulation )
{
   if( m_BodyMotion == BodyMotions::BodyMotions_CrouchJog || m_BodyMotion == BodyMotions::BodyMotions_CrouchIdle)
      {
      Super::UnCrouch( bClientSimulation );
      WakePlayer();
      FVector aimArmRelativeLocation = m_AimingArm->GetRelativeTransform( ).GetLocation( );
      m_AimingArm->SetRelativeLocation( FVector( aimArmRelativeLocation.X, aimArmRelativeLocation.Y, 70.f ) );

      m_BodyMotion = ( m_BodyMotion == BodyMotions::BodyMotions_CrouchJog )?
            m_BodyMotion = BodyMotions::BodyMotions_Jog:
            m_BodyMotion = BodyMotions::BodyMotions_Idle;
      }
}

void ABasicCharacter::SetViewType( PlayerViews inViewType )
{
   switch( inViewType )
      {
         case PlayerViews::PlayerViews_ThirdPerson:
            SetViewTypeToThirdPerson( );
            break;
      case PlayerViews::PlayerViews_Aim:
            SetViewTypeToAim( );
            break;
      case PlayerViews::PlayerViews_FirstPerson:
            SetViewTypeToFirstPerson( );
            break;
      //default:
      }
}

void ABasicCharacter::MoveForward( float amount )
{
   WakePlayer();
   FVector fwd = m_PlayerCamera->GetForwardVector();
   AddMovementInput( fwd, amount );
}

void ABasicCharacter::MoveRight( float amount )
{
   WakePlayer();
   FVector right = m_PlayerCamera->GetRightVector();
   AddMovementInput( right, amount );
}

void ABasicCharacter::SetCameraYaw( float amount )
{
   switch( m_PlayerView )
      {
         case PlayerViews::PlayerViews_ThirdPerson :
            m_ThirdPersonArmYaw->AddRelativeRotation( FRotator( 0, m_CameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
            break;
         case PlayerViews::PlayerViews_Aim:
      //      AddActorWorldRotation( FRotator( 0, m_CameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0 ) );
    //        break;
         case PlayerViews::PlayerViews_FirstPerson :
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
   switch( m_PlayerView )
      {
      case PlayerViews::PlayerViews_ThirdPerson :
         m_ThirdPersonArmPitch->AddRelativeRotation( FRotator( m_CameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
         currentRotation = m_ThirdPersonArmPitch->GetComponentRotation( );
         clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, m_PitchRotLowerBound, m_PitchRotUpperBound );
         m_ThirdPersonArmPitch->SetWorldRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
         break;
      case PlayerViews::PlayerViews_Aim:
        /// m_PlayerCamera->AddRelativeRotation( FRotator( m_CameraRotateSpeed * amount * GetWorld( )->GetDeltaSeconds( ), 0, 0 ) );
     //    cuttrntTransform = m_PlayerCamera->GetRelativeTransform( );
       //  currentRotation = cuttrntTransform.Rotator( );
      //   clampedPitch = FMath::Clamp<float>( currentRotation.Pitch, m_PitchRotLowerBound, m_PitchRotUpperBound );
      //   m_PlayerCamera->SetRelativeRotation( FRotator( clampedPitch, currentRotation.Yaw, currentRotation.Roll ) );
      //   break;
      case PlayerViews::PlayerViews_FirstPerson:
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

//reset idle time and set its bodymotion
void ABasicCharacter::WakePlayer()
{
   m_IdleTime = 0.f;
   if( m_BodyMotion == BodyMotions::BodyMotions_Break )
      {
      m_BodyMotion = BodyMotions::BodyMotions_Idle;
      }
}

void ABasicCharacter::AddIdleTime( float inTime )
{
   m_IdleTime += inTime;
}

void ABasicCharacter::RefineMotionType( float DeltaSeconds )
{
   switch( m_BodyMotion )
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
         m_BodyMotion = BodyMotions::BodyMotions_Jog;
         }
      else //On ground and barely not moving
         {
         m_BodyMotion = BodyMotions::BodyMotions_Idle;
         if( m_ArmMotion == ArmMotions::ArmMotions_Default )//player is not busying using weapon
            {
            m_IdleTime += DeltaSeconds;
            if( m_IdleTime >= 12.6f )
               {
               m_BodyMotion = BodyMotions::BodyMotions_Break;
               }
            }
         }
      }
   else //is falling
      {
      m_BodyMotion = BodyMotions::BodyMotions_Fall;
      }
}

void ABasicCharacter::RefineMotionCrouch( )
{
   if( !GetMovementComponent( )->IsFalling( ) )//Is NOT falling
      {
      if( GetVelocity( ).Size( ) <= 5.f )//On ground and barely not moving
         {
         m_BodyMotion = BodyMotions::BodyMotions_CrouchIdle;
         }
      else
         {
         m_BodyMotion = BodyMotions::BodyMotions_CrouchJog;
         }
      }
   else //is falling
      {
       m_BodyMotion = BodyMotions::BodyMotions_Fall;
      }
 
}

void ABasicCharacter::RefineMotionFall()
{
   if( !GetMovementComponent( )->IsFalling( ) )//Is NOT falling
      {
         if( GetVelocity( ).Size( ) <= 5.f )//On ground and barely not moving
            {
            m_BodyMotion = BodyMotions::BodyMotions_CrouchIdle;
            }
         else
            {
            m_BodyMotion = BodyMotions::BodyMotions_CrouchJog;
           }
      }
}

void ABasicCharacter::RefineMotionJump( )
{
   //if NOT falling(stay on ground)
   if( !GetMovementComponent( )->IsFalling( ) )
      {
      m_BodyMotion = BodyMotions::BodyMotions_Idle;
      }
}

void ABasicCharacter::RefineMotionJogJump( )
{
   //if NOT falling(stay on ground)
   if( !GetMovementComponent( )->IsFalling( ) )
   {
   m_BodyMotion = BodyMotions::BodyMotions_Jog;
   }
}

void ABasicCharacter::RefineMotionBreak( )
{
   if( GetVelocity( ).Size( ) > 5.f )
    {
    m_BodyMotion = BodyMotions::BodyMotions_Idle;
    }
}

void ABasicCharacter::SetViewTypeToThirdPerson( )
{
   GetCharacterMovement( )->bOrientRotationToMovement = true;
   GetMesh( )->SetVisibility( true );
   m_PlayerCamera->AttachTo( m_ThirdPersonArmPitch );
   FRotator currentActorRotation = GetActorRotation( );
   m_ThirdPersonArmYaw->SetWorldRotation( FRotator( currentActorRotation.Pitch, currentActorRotation.Yaw, currentActorRotation.Roll ) );
   m_PlayerCamera->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
   m_PlayerView = PlayerViews::PlayerViews_ThirdPerson;
   m_ArmMotion = ArmMotions::ArmMotions_Default;
}

void ABasicCharacter::SetViewTypeToAim( )
{
   GetCharacterMovement( )->bOrientRotationToMovement = false;
   GetMesh( )->SetVisibility( true );
   m_AimingArm->SetRelativeRotation( FRotator::ZeroRotator );
   SetActorRotation( FRotator( GetActorRotation( ).Pitch, m_PlayerCamera->GetComponentRotation( ).Yaw, GetActorRotation( ).Roll ) );
   m_PlayerCamera->AttachTo( m_AimingArm );
   m_PlayerCamera->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
   m_PlayerView = PlayerViews::PlayerViews_Aim;
   m_ArmMotion = ArmMotions::ArmMotions_IronSight;
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
   m_ArmMotion = ArmMotions::ArmMotions_IronSight;
   m_PlayerView = PlayerViews::PlayerViews_FirstPerson;
   //m_PlayerCamera->Att
}

void UpdateCameraLocationAndRotation( float DeltaSeconds )
 {
 }