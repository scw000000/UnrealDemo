// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DemoEnums.h"
#include "BasicCharacter.generated.h"

UCLASS()
class DEMO_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
   ABasicCharacter( const FObjectInitializer& ObjectInitializer );

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

   virtual void Jump( ) override;

   virtual void ToggleProne();
   	
   virtual void StartAttack();

   virtual void StopAttack();

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

   virtual void Crouch( bool bClientSimulation = false ) override;

   virtual void UnCrouch( bool bClientSimulation = false ) override;

   

   void SetPlayerView( PlayerViews inViewType );
   
   //custom function for movement
   virtual void MoveForward( float amount );

   //custom function for movement
   virtual void MoveRight( float amount );

   void SetCamYaw( const float& amount );

   void SetCamPitch( const float& amount );

   void SetCamDistance( const float& amount );

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      float maxCameraPitch;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      float minCameraPitch;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      float cameraScrollSpeed;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      float cameraRotateSpeed;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      float maxCameraDistance;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      float minCameraDistance;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerMotion )
      float idleTime;

   float health;

   float maxHealth;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* thirdPersonCameraBoomYaw;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* thirdPersonCameraBoomPitch;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      UCameraComponent* playerCamera;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* aimingCameraBoom;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerView )
      PlayerViews playerView;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerMotion )
      ArmMotions armMotion;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = PlayerMotion )
      BodyMotions bodyMotion;


protected:
  void WakePlayer();

  void AddIdleTime( const float& inTime );

  void RefineMotionType( const float& DeltaSeconds );

  void RefineMotionStand( const float& DeltaSeconds );

  void RefineMotionJog( );

  void RefineMotionCrouch( );

  void RefineMotionFall();

  void RefineMotionJump( );

  void RefineMotionJogJump( );

  void RefineMotionBreak( );

private:
   void SetPlayerViewToThirdPerson( );

   void SetPlayerViewToAim( );

   void SetPlayerViewToFirstPerson( );

   void UpdateCameraLocationAndRotation( const float& DeltaSeconds );
};
