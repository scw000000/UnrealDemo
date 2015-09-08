// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DemoPlayerController.generated.h"

class ABasicCharacter;
/**
 * 
 */
UCLASS()
class DEMO_API ADemoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
   virtual void SetupInputComponent( ) override;

   void SpacePressed();

   void BPressed();

   void BReleased();

   void CPressed( );

   void RMBPressed( );

   void RMBReleased( );

   void LeftMouseButtonPressed();

   void LeftMouseButtonReleased();

   void LeftCtrlPressed( );

   void LeftCtrlReleased( );

   void MouseWheelUpPressed();

   void MouseWheelDownPressed( );

   UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Pawn" )
      virtual void Possess( APawn * InPawn ) override;

   //custom function for movement
   void WS( float amount );

   //custom function for movement
   void AD( float amount );

   //custom function for movement
   void MouseX( float amount );

   //custom function for movement
   void MouseY( float amount ); 

   

protected:
   ABasicCharacter* controllingCharacter;
   virtual bool SetControllingCharacter( APawn* InPawn );
};
