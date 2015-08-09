// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ViewablePlayerController.h"
#include "DemoPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoPlayerController : public AViewablePlayerController
{
	GENERATED_BODY()
	
   virtual void SetupInputComponent( ) override;

   // Called when the game starts or when spawned
   //virtual void BeginPlay( ) override;

   //void Tick( float DeltaTime ) override;

   // custom function for movement
   void MoveForward( float amount );

   // custom function for movement
   void MoveRight( float amount );
	
   // custom function for movement
   void Jump( );
};
