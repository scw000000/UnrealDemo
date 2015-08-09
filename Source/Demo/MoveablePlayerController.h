// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.h"
#include "MoveablePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AMoveablePlayerController : public ABasicPlayerController
{
	GENERATED_BODY()
	
public:
   // Sets default values for this character's properties
   //AMoveablePlayerController( const FObjectInitializer& ObjectInitializer );

   virtual void SetupInputComponent( ) override;

   // Called when the game starts or when spawned
   //virtual void BeginPlay( ) override;

   //void Tick( float DeltaTime ) override;

   // custom function for movement
   void MoveForward( float amount );

   // custom function for movement
   void MoveRight( float amount );
	
};
