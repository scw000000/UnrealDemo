// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CameraBoom.h"
#include "SingleArmCameraBoom.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ASingleArmCameraBoom : public ACameraBoom
{
	GENERATED_BODY()
public:
   ASingleArmCameraBoom( const FObjectInitializer& ObjectInitializer );

   virtual void Yaw( float amount ) override;

   virtual void Pitch( float amount ) override;

   virtual USceneComponent* GetCameraAttachComponent( ) override;

   virtual bool AttachToCharacter( ABasicCharacter *inCharacter ) override;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_CameraBoom;
	
};
