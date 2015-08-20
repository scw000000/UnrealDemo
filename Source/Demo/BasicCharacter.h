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

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

   void SetViewType( PlayerViewTypes inViewType );
   
   //custom function for movement
   void MoveForward( float amount );

   //custom function for movement
   void MoveRight( float amount );

   void SetCameraYaw( float amount );

   void SetCameraPitch( float amount );

   void SetCameraDistance( float amount );

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float m_PitchRotUpperBound;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float m_PitchRotLowerBound;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float m_CameraScrollSpeed;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float m_CameraRotateSpeed;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float m_CameraDisUpperBound;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      float m_CameraDisLowerBound;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_ThirdPersonArmYaw;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_ThirdPersonArmPitch;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      UCameraComponent* m_PlayerCamera;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_AimingArm;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = PlayerView )
      PlayerViewTypes m_CurrentViewType;

private:
   void SetViewTypeToThirdPerson( );

   void SetViewTypeToAim( );

   void SetViewTypeToFirstPerson( );

   void UpdateCameraLocationAndRotation( float DeltaSeconds );
};
