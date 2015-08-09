// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CameraBoom.h"
#include "ThirdPersonCameraBoom.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AThirdPersonCameraBoom : public ACameraBoom
{
	GENERATED_BODY()
public:
   AThirdPersonCameraBoom( const FObjectInitializer& ObjectInitializer );

   virtual void Yaw( float amount ) override;

   virtual void Pitch( float amount ) override;

   virtual USceneComponent* GetCameraAttachComponent( ) override;

   virtual bool AttachToCharacter( ABasicCharacter *inCharacter ) override;

   virtual FName GetSocketName( ) override;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      UBoxComponent* m_CharacterCenter;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_CameraBoomYaw;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_CameraBoomPitch; 
	
	
};
