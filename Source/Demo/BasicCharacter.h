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
   	
   void StartAttack();

   void EndAttack();

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

   virtual void Crouch( bool bClientSimulation = false ) override;

   virtual void UnCrouch( bool bClientSimulation = false ) override;

   

   void SetPlayerView( PlayerViews inViewType );
   
   //custom function for movement
   virtual void MoveForward( float amount );

   //custom function for movement
   virtual void MoveRight( float amount );

   void SetCamYaw( float amount );

   void SetCamPitch( float amount );

   void SetCamDistance( float amount );

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float camPitchMax;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float camPitchMin;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float camScrollSpeed;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float camRotSpeed;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float camDistanceMax;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float camDistanceMin;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = PlayerMotion )
      float idleTime;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* thirdPersonCamBoomYaw;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* thirdPersonCamBoomPitch;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      UCameraComponent* playerCam;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* aimingCamBoom;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = PlayerView )
      PlayerViews playerView;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = PlayerMotion )
      ArmMotions armMotion;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = PlayerMotion )
      BodyMotions bodyMotion;


protected:
  void WakePlayer();

  void AddIdleTime( float inTime );

  void RefineMotionType( float DeltaSeconds );

  void RefineMotionStand( float DeltaSeconds );

  void RefineMotionJog( );

  void RefineMotionCrouch( );

  void RefineMotionFall();

  void RefineMotionJump( );

  void RefineMotionJogJump( );

  void RefineMotionBreak( );

  float m_Speed;

private:
   void SetPlayerViewToThirdPerson( );

   void SetPlayerViewToAim( );

   void SetPlayerViewToFirstPerson( );

   void UpdateCameraLocationAndRotation( float DeltaSeconds );
};
