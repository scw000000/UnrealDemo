// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CameraBoom.generated.h"

class ABasicCharacter;

UCLASS( abstract )
class DEMO_API ACameraBoom : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraBoom();

   virtual void Yaw( float amount  );

   virtual void Pitch( float amount );
	
   virtual USceneComponent* GetCameraAttachComponent( );

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

   virtual bool AttachToCharacter( ABasicCharacter *inCharacter );

   virtual FName GetSocketName( );

   
	
   
};
